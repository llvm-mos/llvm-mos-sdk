#include <new>
#include <cstdint>
#include <stdio.h>

extern std::byte __heap_start;

namespace
{

    // An arbitrary block of memory. This struct only holds the size of the block,
    // and the data in the block directly follows
    struct block
    {
        block(std::size_t size) : m_size { size } {}

        static block * get_block(std::byte * data) noexcept
        {
            return reinterpret_cast<block *>(data - sizeof(m_size));
        }

        std::size_t m_size;

        std::byte * data() noexcept { return static_cast<std::byte *>(m_data); }

        std::byte   m_data[]; 
    };

    static_assert(sizeof(block) == sizeof(std::size_t), "!!!");

    // A doubly-linked list of blocks of memory.
    // The next node pointer, the previous node pointer, and the size of the block
    // are stored at the beginning of the block. 
    class blocklist
    {
        // pointers to next and previous.
        struct list_node
        {
            list_node *m_next = nullptr;
            list_node *m_prev = nullptr;
        };

        // The entire block node pointer, which is embedded in the block itself.
        struct block_node : public list_node
        {
            block_node(std::size_t initsz)
                : m_block{initsz - sizeof(block_node)} {}

            block     m_block;

            static block_node * get_node(block & blk)
            {
                return reinterpret_cast<block_node *>(
                    reinterpret_cast<std::byte *>(&blk) - sizeof(list_node));
            }
        };

    public:
        static constexpr std::uint8_t MIN_ALLOC_SIZE = sizeof(block_node) + 2;

        blocklist()
        {
            m_heap_limit = m_heap_limit == SIZE_MAX ? HEAP_DEFAULT_LIMIT : m_heap_limit;
            m_head = new (&__heap_start) block_node{m_heap_limit};
            m_used = sizeof(block_node);
            m_free = m_head->m_block.m_size;
        }
        
        struct iterator
        {
        public:
            iterator() = default;
            iterator(block_node *ptr) noexcept : m_ptr{ptr} {}

            block & operator*() const noexcept
            {
                return m_ptr->m_block;
            }

            iterator & operator++() noexcept
            {
                m_ptr = static_cast<block_node *>(m_ptr->m_next);
                return *this;
            }

            bool operator==(const iterator & rhs) const noexcept
            {
                return m_ptr == rhs.m_ptr;
            }

            bool operator!=(const iterator & rhs) const noexcept
            {
                return !this->operator==(rhs);
            }

        private:
            block_node *m_ptr = nullptr;
        };

        iterator begin()
        {
            return m_head;
        }

        iterator end()
        {
            return iterator{};
        }

        static_assert(sizeof(list_node) == sizeof(list_node::m_next) + sizeof(list_node::m_prev), "unexpected padding");
        static_assert(sizeof(block_node) == sizeof(list_node) + sizeof(std::size_t), "unexpected padding");
 
        std::byte * split_block(block *freeblock, std::size_t size) noexcept
        {
            if (!freeblock)
            {
                return nullptr;
            }

            if ((freeblock->m_size - size) >= blocklist::MIN_ALLOC_SIZE)
            {
                const auto new_blk = new (freeblock->data() + size) block_node{freeblock->m_size - size};
                freeblock->m_size = size;

                const auto freeblock_node_ptr = block_node::get_node(*freeblock);
                {
                    const auto next_block_ptr = new_blk->m_next = freeblock_node_ptr->m_next;
                    if (next_block_ptr)
                    {
                        next_block_ptr->m_prev = new_blk;
                    }
                }

                const auto prev_block_ptr = new_blk->m_prev = freeblock_node_ptr->m_prev;
                if (prev_block_ptr)
                {
                    prev_block_ptr->m_next = new_blk;
                }
                else
                {
                    m_head = new_blk;
                }

                // new node in free list was allocated, remove it from the total bytes free.
                m_used += sizeof(block_node);
                m_free -= sizeof(block_node);
            }
            else
            {
                // drop the block from the free list entirely.
                const auto freeblock_node_ptr = block_node::get_node(*freeblock);
                const auto prev_block_ptr = freeblock_node_ptr->m_prev;
                const auto next_block_ptr = freeblock_node_ptr->m_next;
                
                if (prev_block_ptr)
                {
                    prev_block_ptr->m_next = next_block_ptr;
                }
                else
                {
                    m_head = static_cast<block_node *>(next_block_ptr);
                }
                
                if (next_block_ptr)
                {
                    next_block_ptr->m_prev = prev_block_ptr;
                }
            }

            // update stats for actual size allocated
            m_used += freeblock->m_size;
            m_free -= freeblock->m_size;
            return freeblock->data();
        }

        block *find_first_fit(std::size_t sz) noexcept
        {
            for (auto &block : *this)
            {
                if (block.m_size >= (sz + sizeof(block_node)))
                {
                    return &block;
                }
            }

            return nullptr;
        }

        void free_block(block * const block) noexcept
        {
            block_node * last_block_node = nullptr;
            for (auto & free_blk : *this)
            {
                if (&free_blk > block)
                {
                    const auto freed_block_ptr = block_node::get_node(*block);
                    const auto next_block_ptr = block_node::get_node(free_blk);
                    const auto prev_block_ptr = next_block_ptr->m_prev;

                    freed_block_ptr->m_next = next_block_ptr;
                    next_block_ptr->m_prev = freed_block_ptr;
                    freed_block_ptr->m_prev = prev_block_ptr;
                    
                    if (prev_block_ptr)
                    {
                        prev_block_ptr->m_next = freed_block_ptr;
                    }
                    else
                    {
                        m_head = freed_block_ptr;
                    }

                    m_free += block->m_size;
                    m_used -= block->m_size;
                    return;
                }

                last_block_node = block_node::get_node(free_blk);
            }

            const auto freed_block_ptr = block_node::get_node(*block);
            last_block_node->m_next = freed_block_ptr;
            freed_block_ptr->m_prev = last_block_node;
            freed_block_ptr->m_next = nullptr;
            m_free += block->m_size;
            m_used -= block->m_size;
        }

        void coallesce_blocks() noexcept
        {
            block * last_block = nullptr;

            for (auto & block : *this)
            {
                if (last_block)
                {
                    const auto block_node_ptr = block_node::get_node(block);
                    if (static_cast<void *>(last_block->data() + last_block->m_size) 
                        == static_cast<void *>(block_node_ptr))
                    {
                        // two free sequential blocks.
                        last_block->m_size += sizeof(*block_node_ptr) + block.m_size;
                        const auto last_block_node = block_node::get_node(*last_block);
                        last_block_node->m_next = block_node_ptr->m_next;
                        if (last_block_node->m_next)
                        {
                            last_block_node->m_next->m_prev = last_block_node;
                        }
                        m_used -= sizeof(block_node);
                        m_free += sizeof(block_node);
                        continue;
                    }
                }

                last_block = &block;
            }
        }

        void set_new_limit(std::size_t new_limit)
        {
            if (new_limit >= (m_heap_limit + MIN_ALLOC_SIZE))
            {
                add_block(
                    // new block address will be directly after the region defined by the previous limit.
                    &__heap_start + m_heap_limit,
                    new_limit - m_heap_limit
                );

                m_heap_limit = new_limit;
            }
        }

        // void dump()
        // {
        //     for (const auto & block : *this)
        //     {
        //         printf("BLOCK %p LEN %u\n", &block, block.m_size+sizeof(block_node));
        //     }
        // }

    private:
        // nodes are added at the end of the list.
        void add_node(block_node * node)
        {
            list_node * node_last = m_head;
            for (; node_last->m_next; node_last = node_last->m_next) {}

            node_last->m_next = node;
            node->m_prev = node_last;
        }

        void add_block(std::byte *address, std::size_t size)
        {
            // assume zero alignment padding.
            add_node(new (address) block_node{size});
            m_used += sizeof(block_node);
            m_free += m_head->m_block.m_size;
        }

        block_node *m_head = nullptr;

    public:
        // heap limit is essentially a global var.  It can 
        // be set prior to ctor of blocklist.
        static constexpr std::size_t HEAP_DEFAULT_LIMIT = 4096;
        static std::size_t m_heap_limit;

        // accounting.
        std::size_t m_free = 0;
        std::size_t m_used = 0;
    };

    blocklist &get_free_list() noexcept
    {
        static blocklist free_list;
        return free_list;
    }

    void run_new_handler()
    {
        const auto newp = std::get_new_handler();
        if (newp)
        {
            newp();
        }
    }
}

std::size_t blocklist::m_heap_limit = SIZE_MAX;

void * operator new(std::size_t size)
{
    const auto block = operator new(size, std::nothrow);
    if (!block)
    {
        run_new_handler();
    }

    return block;
}


void * operator new[](std::size_t size)
{
    return operator new(size);
}

void * operator new(std::size_t count, const std::nothrow_t &) noexcept
{
    auto &free_list = get_free_list();
    return free_list.split_block(free_list.find_first_fit(count), count);
}

void *operator new[](std::size_t count, const std::nothrow_t &) noexcept
{
    return operator new(count, std::nothrow);
}

void * operator new(std::size_t, void *ptr)
{
    return ptr;
}

void * operator new[](std::size_t, void *ptr)
{
    return ptr;
}

void operator delete(void *ptr) noexcept
{
    if (!ptr)
    {
        return;
    }
    
    auto &free_list = get_free_list();
    free_list.free_block(block::get_block(static_cast<std::byte *>(ptr)));
    free_list.coallesce_blocks();
}

void operator delete[](void * ptr) noexcept
{
    operator delete(ptr);
}

// helper functions for getting/setting flags in guard_object
static bool initializerHasRun(std::uint8_t * guard_object)
{
    return (*guard_object != 0);
}

static void setInitializerHasRun(std::uint8_t *guard_object)
{
    *(guard_object) = 1;
}

extern "C"
{
int __cxa_guard_acquire(std::uint8_t *guard_object)
{
    // Double check that the initializer has not already been run
    if (initializerHasRun(guard_object))
    {
        return 0;
    }
    return 1;
}

void __cxa_guard_release(std::uint8_t * guard_object)
{
    setInitializerHasRun(guard_object);
}
}

namespace std
{
    namespace
    {
        new_handler current_new_handler = nullptr;
    }

    new_handler get_new_handler() noexcept
    {
        return current_new_handler;
    }

    new_handler set_new_handler(new_handler new_p) noexcept
    {
        auto old_handler = current_new_handler;
        current_new_handler = new_p;
        return old_handler;
    }
}

extern "C"
{
    
size_t heap_limit()
{
    return blocklist::m_heap_limit == SIZE_MAX ? blocklist::HEAP_DEFAULT_LIMIT : blocklist::m_heap_limit;
}

void set_heap_limit(size_t new_size)
{
    // uninitialized.
    if (blocklist::m_heap_limit == SIZE_MAX)
    {
        blocklist::m_heap_limit = (new_size < blocklist::MIN_ALLOC_SIZE)
            ? blocklist::MIN_ALLOC_SIZE
            : new_size;
    }
    else
    {
        get_free_list().set_new_limit(new_size);
    }
}

size_t heap_bytes_used()
{
    return get_free_list().m_used;
}

size_t heap_bytes_free()
{
    return get_free_list().m_free;
}

}

// void dump()
// {
//     get_free_list().dump();
// }
