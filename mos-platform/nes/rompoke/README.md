# rompoke.h - "safe" ROM writing for mappers with bus conflicts

The NES features mapper bus conflicts. Simpler mappers, based around discrete logic chips, do not prevent the ROM chip from being enabled when the CPU is writing to the cartridge's data bus - this creates a conflict, as both the CPU and ROM are outputting values on the same bus at the same time.

The correct way to work around this is to ensure that the value output by the CPU is the same as outputting the ROM. This is typically done by creating a byte array `A` where, for any given value `N`, `A[N] == N`; then, whenever one wants to write `N` to ROM, it is done to the address of `A[N]`.

However, this byte array would normally take up 256 bytes of the 16384 bytes typically present in the "fixed" ROM. Many mappers only require a far smaller table; for example, an UNROM cartridge typically only has 16 banks, so the only values one would need to write to the ROM bus will be between 0 and 15.

The solution presented here - `rompoke.*` and `rompoke-table.ld` - allows the LLVM-MOS SDK to dynamically allocate, at link time, a minimally-sized array based on the INES header configuration.

## Adding a new mapper

To add a new mapper, one has to define a file called `_rompoke.ld` in their mapper's directory. This file will determine the size of the byte array `A`, from 0 - no bus conflicts - to 256 bytes. As such, at its simplest, one can define the file as follows:

```
__rom_poke_table_size = 256;
```

This will be functional, if usually wasteful of ROM space. Ideally, one would vary this value dynamically depending on the configuration of the INES header. At the same time, however, typing all the necessary conditions by hand would be tedious, especially for mappers with more than one variable - this is where `generate-rompoke-mapper-linkscript.lua` comes in. The script will generate the necessary `_rompoke.ld` file for you; it requires Lua 5.4.

To add a new mapper to the generator script, one should populate the `CONFIG_MAP` table at the top of the script with a new key, corresponding to their mapper. The value should be in the form of a table containing the mapper's bitfields in order.

Let's use the example of a simple mapper - UNROM. It is defined as follows:

```
7  bit  0
---- ----
pppp PPPP
|||| ||||
++++-++++- 16K PRG-ROM bank ID
           Mapped at $8000-$BFFF
```

A ROM with 256 PRG-ROM banks would take up 4 MB. Most games are considerably smaller than this; for example, a 256 KB game will only use 16 banks, and thus require safe ROM write support for values 0 - 15 only.

Let's codify this in the link script's configuration format. Each bitfield is defined using a table which can have one of the following formats:

* `{bitwidth, nil}` - can be 0 or 1 irrespective of INES configuration,
* `{bitwidth, 0}` - always 0,
* `{bitwidth, 1}` - always 1,
* `{bitwidth, expr, comparator[, step]}` - conditional based on value of expression:
  * `>`: `value` is maximum if `expr > (value * step)`,
  * `>log2`: as above, but in log2(...) progression; for a step of 16, values {16, 32, 64, 128, ...} would be used,
  * `==`: `value` is maximum if `expr` is true.

For UNROM, we'd like to use the `>log2` conditional comparator for each 16K PRG-ROM bank. The linker defines a `__prg_rom_size` value in kilobytes; as such, one can model it as follows:

```
{
    8, -- 8 bit-wide field
    "__prg_rom_size", -- expression
    ">log2", -- conditional comparator
    16 -- step
}
```

In addition, one can define a condition under which no bus conflicts occur - in this case, an empty table will be generated, occupying no ROM space. For UNROM, this is the case when the `__submapper` value is 1; one can then write the following into their script:

```
["none_if"] = "__submapper == 1"
```

Once you've defined the configuration for your mapper, call `lua generate-rompoke-mapper-linkscript.lua unrom-512 > ../../../nes-unrom512/_rompoke.ld`. You're done!



