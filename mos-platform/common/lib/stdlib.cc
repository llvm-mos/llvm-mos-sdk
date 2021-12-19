#include "stdlib.h"

#include <new>

extern "C"
{
    void *malloc(size_t size)
    {
        return new (std::nothrow) std::byte[size];
    }

    void free(void * ptr)
    {
        delete [] static_cast<std::byte *>(ptr);
    }

    void __memset(char *ptr, char value, size_t num);
    void *memcpy(void *dest, const void *src, size_t count);
    
    void *calloc(size_t num, size_t size)
    {
        const auto sz = num*size;
        const auto block = malloc(sz);
        
        if (!block)
        {
            return nullptr;
        }

        __memset(static_cast<char *>(block), 0, sz);
        return block;
    }
}
