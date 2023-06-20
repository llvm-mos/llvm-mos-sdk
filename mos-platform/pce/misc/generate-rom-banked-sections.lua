-- Copyright (c) 2023 Adrian "asie" Siekierka
--
-- Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
-- See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
-- information.

local NON_FIXED_ROM_VBANK_0 = true
local VBANK_MAX = 128
local BANK_KB = 8

function printf(...)
	print(string.format(table.unpack({...})))
end

local VBANK_START = 0
if NON_FIXED_ROM_VBANK_0 then
	-- Custom handling for non-fixed vbank0 (split into 8KB 0a and remainer 0b).
	VBANK_START = 1
end

print("/* Automatically generated by generate-rom-banked-sections.lua. */\n")

-- for each bank, define "offset", "size"
-- bank 0 has special handling - fixed 8KB bank at $E000 + non-fixed extra bank below it
if NON_FIXED_ROM_VBANK_0 then
	printf("PROVIDE(__rom_vbank_0 = 0xe000);")
	printf("PROVIDE(__rom_vbank_0_size = 0x2000);")
	printf("__rom_vbank_0a = 0xe000;")
	printf("__rom_vbank_0a_size = 0x2000;")
	printf("__rom_vbank_0a_offset = 0;")
	printf("__rom_vbank_0b = 0x10000 - __rom_vbank_0_size;")
	printf("__rom_vbank_0b_size = __rom_vbank_0_size - 0x2000;")
	printf("__rom_vbank_0b_offset = 0x2000;")
	printf("HIDDEN(__rom_vbank_0_offset = 0);")
else
	printf("__rom_vbank_0 = 0xe000;")
	printf("__rom_vbank_0_size = 0x2000;")
	printf("__rom_vbank_0_offset = 0;")
end
-- banks 1+ - empty bank placeholders
for i = 1,VBANK_MAX-1 do
	printf("PROVIDE(__rom_vbank_%d = 0x4000);", i)
	printf("PROVIDE(__rom_vbank_%d_size = 0);", i)
	printf("__rom_vbank_%d_offset = __rom_vbank_%d_offset + __rom_vbank_%d_size;", i, i-1, i-1)
end
if NON_FIXED_ROM_VBANK_0 then
	-- Provide fake LMA/bank/offset mapping for llvm-mlb.
	printf("__rom_vbank_0a_bank = 0;")
	printf("__rom_vbank_0a_lma = __rom_vbank_0a;")
	printf("__rom_vbank_0b_bank = 1;")
	printf("__rom_vbank_0b_lma = __rom_vbank_0b;")
end
for i = VBANK_START,VBANK_MAX-1 do
	printf("__rom_vbank_%d_bank = __rom_vbank_%d_offset >> 13;", i, i)
	printf("__rom_vbank_%d_lma = (__rom_vbank_%d_bank << 16) + __rom_vbank_%d;", i, i, i)
end

printf("__rom_vbank_end_offset = __rom_vbank_%d_offset + __rom_vbank_%d_size;", VBANK_MAX-1, VBANK_MAX-1);
printf("ASSERT(__rom_vbank_end_offset <= %d, \"ROM size cannot be larger than %d KB.\");", VBANK_MAX*BANK_KB*1024, VBANK_MAX*BANK_KB)

-- define memory sections
printf("")
printf("MEMORY {")
if NON_FIXED_ROM_VBANK_0 then
	printf("  rom_vbank_0 : ORIGIN = __rom_vbank_0b_lma, LENGTH = __rom_vbank_0_size")
end
for i = VBANK_START,VBANK_MAX-1 do
	printf("  rom_vbank_%d : ORIGIN = __rom_vbank_%d_lma, LENGTH = __rom_vbank_%d_size", i, i, i)
end
printf("}")

printf("")
printf("SECTIONS {")
for i = 0,VBANK_MAX-1 do
	printf("  .rom_vbank_%d : { *(.rom_vbank_%d .rom_vbank_%d.*) } >rom_vbank_%d", i, i, i, i)
end
printf("}")

printf("")
printf("OUTPUT_FORMAT {")
if NON_FIXED_ROM_VBANK_0 then
	printf("  FULL(rom_vbank_0, __rom_vbank_0_size - 0x2000, 0x2000)")
	printf("  FULL(rom_vbank_0, 0, __rom_vbank_0_size - 0x2000)")
end
for i = VBANK_START,VBANK_MAX-1 do
	printf("  FULL(rom_vbank_%d)", i)
end
printf("}")
