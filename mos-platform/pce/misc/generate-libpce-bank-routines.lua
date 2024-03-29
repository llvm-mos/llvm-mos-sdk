-- Copyright (c) 2023 Adrian "asie" Siekierka
--
-- Licensed under the Apache License, Version 2.0 with LLVM Exceptions,                                   
-- See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license                             
-- information.

local BANK_MIN = 0
local BANK_MAX = 7
local BANK_CHAIN_MIN = 2
local BANK_CHAIN_MAX = 6
local GENERATE_ASM_1BANKS = false

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

-- Generate non-chained bankswitching getters/setters.

local args = {...}
for i=BANK_MIN,BANK_MAX do
	if args[1] == "h" then
		printf("/**")
		printf(" * @brief Get the currently mapped bank at offset %d.", i)
		printf(" * @return The bank ID.")
		printf(" */")
		printf("__attribute__((leaf)) uint8_t pce_bank%d_get(void);", i)
		printf("/**")
		printf(" * @brief Map a bank at offset %d.", i)
		printf(" * @param id The bank ID to map.")
		printf(" */")
		printf("__attribute__((leaf)) void pce_bank%d_set(uint8_t id);", i)
	elseif (args[1] == "c") then
		printf("")
		printf("__attribute__((leaf)) uint8_t pce_bank%d_get(void) {", i)
		printf("    uint8_t result;")
		printf("    __attribute__((leaf)) asm volatile(");
		printf("        \"tma #%d\" : \"=a\"(result) : : );", (1 << i))
		printf("    return result;")
		printf("}")
		printf("")
		printf("void pce_bank%d_set(uint8_t id) {", i)
		printf("    __attribute__((leaf)) asm volatile(");
		printf("        \"tam #%d\" : \"+a\"(id) : : );", (1 << i))
		printf("}")
		printf("void pce_bank%d_size%d_set(uint8_t id) __attribute__((alias (\"pce_bank%d_set\")));", i, 1, i)
		printf("void pce_bank%d_size%di_set(uint8_t id) __attribute__((alias (\"pce_bank%d_set\")));", i, 1, i)
	elseif args[1] == "asm" then
		-- pass
	else
		printf("Usage: generate-libpce-bank-routines <c|h|asm>")
		os.exit(1)
	end
end

for i=BANK_CHAIN_MIN,BANK_CHAIN_MAX do
	for j=i+1,BANK_CHAIN_MAX do
		local str = generate_shorthand(i, j)
		local bank_offset = i
		local bank_size = (j - i + 1)

		if args[1] == "h" then
			-- printf("__attribute__((leaf)) void pce_bank%s_set(uint8_t id);", str)
			printf("/**")
			printf(" * @brief Map consecutive banks at offsets from %d to %d inclusive.", i, j)
			printf(" * @param id The first bank ID to map.")
			printf(" */")
			printf("__attribute__((leaf)) void pce_bank%si_set(uint8_t id);", str)
		elseif args[1] == "asm" then
			-- printf(".global pce_bank%s_set", str)
			printf(".global pce_bank%si_set", str)
			-- printf(".global pce_bank%d_size%d_set", bank_offset, bank_size)
			printf(".global pce_bank%d_size%di_set", bank_offset, bank_size)
		end
	end
end

-- Generate chained bankswitching setters.

if args[1] == "asm" then
	if false and GENERATE_ASM_1BANKS then
		printf("")
		printf("    .section .text.bank%d, \"ax\", @progbits", BANK_CHAIN_MIN)
		printf("pce_bank%d_set:", BANK_CHAIN_MIN)
		printf("pce_bank%d_size1_set:", BANK_CHAIN_MIN)
		printf("pce_bank%d_size1i_set:", BANK_CHAIN_MIN)
		printf("    tam #$%02x", 1 << BANK_CHAIN_MIN)
		printf("    rts")
	end

	for i=BANK_CHAIN_MIN+1,BANK_CHAIN_MAX do
		for k=1,1 do
			printf("")
			local incr = (k & 1) ~= 0
			local suffix = ""
			if incr then suffix = suffix .. "i" end
			local str = generate_shorthand(BANK_CHAIN_MIN, i) .. suffix
			printf("    .section .text.bank%s, \"ax\", @progbits", str)
			for j=BANK_CHAIN_MIN,i do
				if (j ~= i) then
					printf("pce_bank%s_set:", str)
					printf("pce_bank%d_size%d%s_set:", j, (i - j + 1), suffix)
				end
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

-- Generate inline push/pop handlers.

if args[1] == "h" then
	for i=BANK_CHAIN_MIN,BANK_CHAIN_MAX do
		for j=i,BANK_CHAIN_MAX do
			printf("")
			printf("static inline void pce_bank%d_size%d_push(void) {", i, (j - i + 1))
			printf("    __attribute__((leaf)) asm volatile (")
			for k=i,j,1 do
				printf("        \"tma #$%02x\\n\"", 1 << k)
				printf("        \"pha\\n\"")
			end
			printf("        \"\" : : : \"a\");")
			printf("}")
			printf("")
			printf("static inline void pce_bank%d_size%d_pop(void) {", i, (j - i + 1))
			printf("    __attribute__((leaf)) asm volatile (")
			for k=j,i,-1 do
				printf("        \"pla\\n\"")
				printf("        \"tam #$%02x\\n\"", 1 << k)
			end
			printf("        \"\" : : : \"a\");")
			printf("}")
		end
	end
end
