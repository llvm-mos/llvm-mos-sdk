/* MOS-specific ELF definitions.
 *
 * © 2022 David Given
 *
 * This file is part of the llvm-mos-sdk project and is redistributable under
 * the terms of the Apache 2.0 license with the LLVM exceptions. See the LICENSE
 * file in the project root for the full text.
 */

#define EM_MOS 6502

/* MOS relocations. */

#define R_MOS_NONE 0
#define R_MOS_IMM8 1
#define R_MOS_ADDR8 2
#define R_MOS_ADDR16 3
#define R_MOS_ADDR16_LO 4
#define R_MOS_ADDR16_HI 5
#define R_MOS_PCREL_8 6
#define R_MOS_ADDR24 7
#define R_MOS_ADDR24_BANK 8
#define R_MOS_ADDR24_SEGMENT 9
#define R_MOS_ADDR24_SEGMENT_LO 10
#define R_MOS_ADDR24_SEGMENT_HI 11
#define R_MOS_PCREL_16 12
#define R_MOS_FK_DATA_4 13
#define R_MOS_FK_DATA_8 14
#define R_MOS_ADDR_ASCIZ 15
#define R_MOS_IMM16 16
#define R_MOS_ADDR13 17

/* ELF structure definitions. */

#define ELF32_EHDR_IDENT offsetof(Elf32_Ehdr, e_ident)
#define ELF32_EHDR_MACHINE offsetof(Elf32_Ehdr, e_machine)
#define ELF32_EHDR_PHENTSIZE offsetof(Elf32_Ehdr, e_phentsize)
#define ELF32_EHDR_PHNUM offsetof(Elf32_Ehdr, e_phnum)
#define ELF32_EHDR_PHOFF offsetof(Elf32_Ehdr, e_phoff)
#define ELF32_EHDR_SHENTSIZE offsetof(Elf32_Ehdr, e_shentsize)
#define ELF32_EHDR_SHNUM offsetof(Elf32_Ehdr, e_shnum)
#define ELF32_EHDR_SHOFF offsetof(Elf32_Ehdr, e_shoff)

#define ELF32_PHDR_TYPE offsetof(Elf32_Phdr, p_type)
#define ELF32_PHDR_FILESZ offsetof(Elf32_Phdr, p_filesz)
#define ELF32_PHDR_MEMSZ offsetof(Elf32_Phdr, p_memsz)
#define ELF32_PHDR_OFFSET offsetof(Elf32_Phdr, p_offset)
#define ELF32_PHDR_PADDR offsetof(Elf32_Phdr, p_paddr)
#define ELF32_PHDR_VADDR offsetof(Elf32_Phdr, p_vaddr)
#define ELF32_PHDR__SIZE sizeof(Elf32_Phdr)

#define ELF32_SHDR_TYPE offsetof(Elf32_Shdr, sh_type)
#define ELF32_SHDR_OFFSET offsetof(Elf32_Shdr, sh_offset)
#define ELF32_SHDR_SIZE offsetof(Elf32_Shdr, sh_size)
#define ELF32_SHDR_ENTSIZE offsetof(Elf32_Shdr, sh_entsize)
#define ELF32_SHDR__SIZE sizeof(Elf32_Shdr)

#define ELF32_SYM_NAME offsetof(Elf32_Sym, st_name)
#define ELF32_SYM_VALUE offsetof(Elf32_Sym, st_value)
#define ELF32_SYM_SHNDX offsetof(Elf32_Sym, st_shndx)
#define ELF32_SYM__SIZE sizeof(Elf32_Sym)

#define ELF32_RELA_INFO offsetof(Elf32_Rela, r_info)
#define ELF32_RELA_OFFSET offsetof(Elf32_Rela, r_offset)
#define ELF32_RELA__SIZE sizeof(Elf32_Rela)
