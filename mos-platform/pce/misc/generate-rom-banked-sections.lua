-- Copyright (c) 2023 Adrian "asie" Siekierka
--
-- Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
-- See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
-- information.

local BANK_MAX = 128
local MPR_MAX = 8
local BANK_KB = 8
local BANK_BYTES = BANK_KB * 1024

function printf(...)
	print(string.format(table.unpack({...})))
end

print("/* Automatically generated by generate-rom-banked-sections.lua. */\n")

-- calculate ROM sizes first, to pad the physical banks
printf("PROVIDE(__rom_bank0 = 0xe000);", i)
printf("PROVIDE(__rom_bank0_size = 0x2000);")
for i = 1,BANK_MAX-1 do
	printf("PROVIDE(__rom_bank%d = 0xc000);", i)
	printf("PROVIDE(__rom_bank%d_size = 0);", i)
end
printf("")
io.write("__rom_size = MAX(")
for i=BANK_MAX-1,1,-1 do
	io.write(string.format("(__rom_bank%d_size > 0 ? 0x%x : ", i, ((i + 1) * BANK_BYTES)))
end
io.write("0")
for i=1,BANK_MAX-1,1 do
	io.write(")")
end
print(", __rom_bank0_size);")

-- Provide VBank-format fake LMA/bank/offset mapping in symbols.
-- This is so that llvm-mlb can properly map the larger fixed bank's symbols.
printf("")
printf("__rom_vbank0a = 0xe000;")
printf("__rom_vbank0a_size = 0x2000;")
printf("__rom_vbank0a_offset = 0;")
printf("__rom_vbank0a_bank = 0;")
printf("__rom_vbank0a_lma = __rom_vbank0a;")
printf("__rom_vbank0b = 0x10000 - __rom_bank0_size;")
printf("__rom_vbank0b_size = __rom_bank0_size - 0x2000;")
printf("__rom_vbank0b_offset = 0x2000;")
printf("__rom_vbank0b_bank = __rom_bank0_size > 0x2000 ? 1 : -1;")
printf("__rom_vbank0b_lma = __rom_vbank0b;")

-- Define _bank symbols.
printf("")
for i = 0,BANK_MAX-1 do
	printf("__rom_bank%d_bank = %d;", i, i)
end

-- Define memory sections and output format.
printf("")
printf("MEMORY {")
printf("  rom_bank0 : ORIGIN = __rom_bank0, LENGTH = __rom_bank0_size")
for i = 1,BANK_MAX-1 do
	local bank_offset = (i + 1) * BANK_BYTES
	if i < MPR_MAX then
		-- Consider __rom_bank0's dynamic size.
		printf("  rom_bank%d : ORIGIN = (0x%06x + __rom_bank%d), LENGTH = (((__rom_size >= 0x%x) && (__rom_bank0_size < 0x%x)) ? 0x2000 : 0)", i, (i << 16), i, bank_offset, bank_offset)
	else
		printf("  rom_bank%d : ORIGIN = (0x%06x + __rom_bank%d), LENGTH = (__rom_size >= 0x%x ? 0x2000 : 0)", i, (i << 16), i, bank_offset)
	end
end
printf("}")

printf("")
printf("SECTIONS {")
for i = 0,BANK_MAX-1 do
	printf("  .rom_bank%d : { *(.rom_bank%d .rom_bank%d.*) } >rom_bank%d", i, i, i, i)
end
printf("}")

printf("")
printf("OUTPUT_FORMAT {")
printf("  FULL(rom_bank0, __rom_bank0_size - 0x2000, 0x2000)")
printf("  FULL(rom_bank0, 0, __rom_bank0_size - 0x2000)")
for i = 1,BANK_MAX-1 do
	printf("  FULL(rom_bank%d)", i)
end
printf("}")
