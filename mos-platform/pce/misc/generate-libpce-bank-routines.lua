-- Copyright (c) 2023 Adrian "asie" Siekierka
--
-- Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
-- See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
-- information.

local BANK_MIN = 2
local BANK_MAX = 6

function printf(...)
	print(string.format(table.unpack({...})))
end

function generate_shorthand(i, j)
	local str = ""
	for k=i,j do
		str = str .. k
	end
	return str
end

local args = {...}
for i=BANK_MIN,BANK_MAX do
	for j=i,BANK_MAX do
		local str = generate_shorthand(i, j)
		local bank_offset = i
		local bank_size = (j - i + 1)
		if args[1] == "c" then
			printf("__attribute__((leaf)) void pce_bank%s_set(uint8_t id);", str)
			printf("__attribute__((leaf)) void pce_bank%si_set(uint8_t id);", str)
		elseif args[1] == "asm" then
			printf(".global pce_bank%s_set", str)
			printf(".global pce_bank%si_set", str)
			printf(".global pce_bank%d_size%d_set", bank_offset, bank_size)
			printf(".global pce_bank%d_size%di_set", bank_offset, bank_size)
		else
			printf("Usage: generate-libpce-bank-routines <c|asm>")
			os.exit(1)
		end
	end
end

if args[1] == "asm" then
	printf("")
	printf("    .section .text.bank%d, \"ax\", @progbits", BANK_MIN)
	printf("pce_bank%d_set:", BANK_MIN)
	printf("pce_bank%di_set:", BANK_MIN)
	printf("pce_bank%d_size1_set:", BANK_MIN)
	printf("pce_bank%d_size1i_set:", BANK_MIN)
	printf("    tam #$%02x", 1 << BANK_MIN)
	printf("    rts")

	for i=BANK_MIN+1,BANK_MAX do
		for k=0,1 do
			printf("")
			local incr = (k & 1) ~= 0
			local suffix = ""
			if incr then suffix = suffix .. "i" end
			local str = generate_shorthand(BANK_MIN, i) .. suffix
			printf("    .section .text.bank%s, \"ax\", @progbits", str)
			for j=BANK_MIN,i do
				printf("pce_bank%s_set:", str)
				printf("pce_bank%d_size%d%s_set:", j, (i - j + 1), suffix)
				printf("    tam #$%02x", 1 << j)
				if incr and (j ~= i) then
					printf("    inc")
				end
				str = str:sub(2)
			end
			printf("    rts")
		end
	end
end
