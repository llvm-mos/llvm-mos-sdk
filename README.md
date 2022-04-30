# LLVM-MOS SDK

The LLVM-MOS compiler toolchain and platform libraries.

## Supported platforms

- Atari 8-bit
- Commodore 64
- NES
  - NES-NROM-128
  - NES-NROM-256
  - NES-SLROM
- 6502 simulator (included)

## Notable features

- Broad C99 and C++11 freestanding standards compatibility
  - Interrupt handling
  - C++ templates
  - C++ virtual functions
  - C++ new/delete
  - C++ Run-Time Type Information (dynamic_cast,  typeid)
  - C++ static constructors/destructors (run before and after main)
  - C++ "magic" function local static constructors/destructors
- The high and low-level optimizations expected of a young-ish LLVM backend 
  - Sophisticated register allocation over A, X, Y, and a field of 16 2-byte zero-page (imaginary) registers
  - The imaginary registers can be placed anywhere and need not be contiguous.
  - The calling convention passes through registers whenever possible. 
  - Loop optimizations to select 6502 addressing modes
  - Whole program "static stack" optimization
    - Automatically identifies non-reentrant functions and allocates their frames as static globals
    - Programs without recursion or complex function pointers may not need a soft stack at all.
    - No manual annotations required
  - Link time inlining and optimization across the whole program
    - Includes SDK libraries. Library calls can be often optimized away completely!
- Excellent compiler usability
  - Clang's world-class error messages
  - IDE integration through the included custom clangd's Language Server Protocol
  - Straigtforward invocations to compile for various targets: `mos-c64-clang++ -Os -o game.prg game.cc` 
- A small standard library sufficient to provide the above and a few extras
  - Simple printf
  - Simple malloc/free
  - exit, _Exit, and atexit
- An ELF file format implementation
  - All the usual POSIX tools for working with object files: readelf, nm, etc.
  - A GAS-compatible assembler for the 6502 with a complete macro system
- A lld linker implementation for the 6502
  - All the usual trimmings of an ELF lld backend
    - Link-time garbage collection
    - Symbol map exports
    - Linker scripts
    - GCC ld compatibility

## Notably missing features

- C99 requires supporting 64KiB locals, sorry, no can do.
- A hosted C with all the standard library bells and whistles.
- Float/double
- C++ Exceptions


## Getting started

### Download

First, download and extract the archive for your platform.

- [Linux](https://github.com/llvm-mos/llvm-mos-sdk/releases/latest/download/llvm-mos-linux.tar.xz)
- [Mac OS](https://github.com/llvm-mos/llvm-mos-sdk/releases/latest/download/llvm-mos-macos.tar.xz)
- [Windows](https://github.com/llvm-mos/llvm-mos-sdk/releases/latest/download/llvm-mos-windows.7z)

### (Optional) Add LLVM-MOS to PATH

If you like, you can add LLVM-MOS to your path. This will make accessing
LLVM-MOS from the command line easier.

**WARNING**: Don't install LLVM-MOS into your path if you already have LLVM/Clang
installed. LLVM-MOS conflicts with other LLVM/Clang installations.

#### POSIX

Add the following line to your shell profile (`~/.bashrc`, `~/.zshrc`, etc...):

```console
export PATH=$PATH:<arbitrary-install-directory>/bin
```

To work with CMake-enabled IDEs, it may also need to be added to your desktop
profile (`~/.gnomerc`,
[KDE](https://userbase.kde.org/Session_Environment_Variables), etc...).

#### Windows

```console
rundll32.exe sysdm.cpl,EditEnvironmentVariables
# Edit "Path" user variable
# Add entry for "<arbitrary-install-directory>\bin"
```

Afterwards, new shells will have direct access to LLVM-MOS.

### Compile an Example

Once installed, you can compile a sample program with a direct command. You will
need to prefix `clang` (or `clang++`) with a specific MOS platform provided by
the SDK. This will ensure clang loads the correct configuration to generate
executables and libraries for that target.

| Platform       | Command              |
| -------------- | ------------------   |
| Atari 8-bit    | `mos-atari8-clang`   |
| Commodore 64   | `mos-c64-clang`      |
| NES-NROM-128   | `mos-nrom-128-clang` |
| NES-NROM-256   | `mos-nrom-256-clang` |
| NES-SLROM      | `mos-slrom-clang`    |
| 6502 simulator | `mos-sim-clang`      |

```console
$ cat <install_dir>/examples/hello-putchar.c
#include <stdio.h>

int main(void) {
  const char *cur = "HELLO, PUTCHAR!\n";
  while (*cur)
    __putchar(*cur++);
  return 0;
}

$ mos-c64-clang -Os -o hello.prg <install_dir>/examples/hello-putchar.c

$ ls -l hello.prg
... 77 ... hello.prg

$ hexdump -C hello.prg
00000000  01 08 0b 08 5d 1e 9e 32  30 36 31 00 00 00 20 1e  |....]..2061... .|
00000010  08 4c 14 08 60 8d 4c 08  20 13 08 ad 4c 08 60 a2  |.L..`.L. ...L.`.|
00000020  01 a9 48 c9 0a f0 10 20  d2 ff bd 3b 08 e8 e0 11  |..H.... ...;....|
00000030  d0 f1 a2 00 a9 00 60 a9  0d 4c 26 08 48 45 4c 4c  |......`..L&.HELL|
00000040  4f 2c 20 50 55 54 43 48  41 52 21 0a 00           |O, PUTCHAR!..|
0000004d

$ mos-c64-clang -Os -o hello.s -Wl,--lto-emit-asm <install_dir>/examples/hello-putchar.c

$ cat hello.s
        .text
        .file   "ld-temp.o"
        .section        .text.main,"ax",@progbits
        .globl  main
        .type   main,@function
main:
        ldx     #1
        lda     #72
.LBB0_1:
        cmp     #10
        beq     .LBB0_4
.LBB0_2:
        ;APP
        jsr     __CHROUT
        ;NO_APP
        lda     .L.str,x
        inx
        cpx     #17
        bne     .LBB0_1
        ldx     #0
        lda     #0
        rts
.LBB0_4:
        lda     #13
        jmp     .LBB0_2
.Lfunc_end0:
        .size   main, .Lfunc_end0-main

...Superfluous ASM...

        .type   .L.str,@object
        .section        .rodata.str1.1,"aMS",@progbits,1
.L.str:
        .asciz  "HELLO, PUTCHAR!\n"
        .size   .L.str, 17

```

Note that the generated ASM output will contain more than actually ends up in
the binary.  This is because this assembly is emitted before a link-time garbage
collection pass discards functions that aren't actually referenced.

### Developing for 6502 with CMake

A CMake package and toolchain file are provided to make targeting MOS from
CMake easy.

Create a new source directory with a `CMakeLists.txt` like the following where
`LLVM_MOS_PLATFORM` is set to any platform supported by the SDK:

```cmake
cmake_minimum_required(VERSION 3.18)
set(LLVM_MOS_PLATFORM c64)
find_package(llvm-mos-sdk REQUIRED)
project(llvm-mos-sdk-foo)
add_executable(foo foo.c)
```

**Note:** If LLVM-MOS was *not* added to PATH, set
`-DCMAKE_PREFIX_PATH=<arbitrary-install-directory>` to match the install prefix
of LLVM-MOS so `find_package` will work correctly.


## Development

To modify the SDK, you'll need to be able to build it yourself. This requires a
working LLVM-MOS compiler, which can be found in the current SDK release.
Accordingly, make sure to install the SDK first using the instructions above.

### Install ninja

For the steps below to work as-is, you'll need to install Ninja, the fast,
parallel build tool favored by LLVM developers. Instructions for your
platform will vary; see https://ninja-build.org/.

Alternatively, you can set -G "Makefile" in each CMake command to use
standard UNIX Makefiles, or you can substitute any other CMake-supported
generator. Your compile times may take a hit, and LLVM is already very slow
to build, so Ninja is highly recommended.

### Build and Install LLVM-MOS-SDK

Set `CMAKE_INSTALL_PREFIX` below to the LLVM-MOS installation directory. This will replace the SDK portion of the installation with the newly built artifacts on `ninja install`.

```console
$ git clone https://github.com/llvm-mos/llvm-mos-sdk.git
$ cd llvm-mos-sdk
$ mkdir build
$ cd build
$ cmake -G "Ninja" -DCMAKE_INSTALL_PREFIX=<sdk-install-directory> ..
$ ninja install
```

The complete SDK will now be present in the install prefix.
