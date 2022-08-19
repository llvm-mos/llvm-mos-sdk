asm(".globl __prg_ram_size\n__prg_ram_size=32\n"
    ".globl __prg_nvram_size\n__prg_nvram_size=32\n");
int main(void) { return 0; }
