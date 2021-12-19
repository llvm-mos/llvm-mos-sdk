// place holder for stdlib "abort" function.

// Not sure what the best way to handle this is on C64.

void abort()
{
    asm volatile("brk" : );
    __builtin_unreachable();
}
