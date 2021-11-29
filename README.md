# LLVM-MOS SDK

A WIP SDK for developing with the llvm-mos compiler.

## Project Status

At present, only one configuration for the Commodore 64 is supported, but
effort is being made to ensure that the SDK generalizes. Before the first
official release, several other first-class targets will be created to
provide examples to aid our users to port to other platforms.

A hello world example application can be built for the C64, but much of the
expected runtime is missing. As the compile approaches C99 compatibility,
this will fill out to become a full frestanding C99 implementation.

## Build

Building the SDK first requires a working LLVM-MOS compiler. There isn't an
official release yet, but if you're eager to try it out, you can compile it yourself.

### Install ninja

For the steps below to work as-is, you'll need to install Ninja, the fast,
parallel build tool favored by LLVM developers. Instructions for your
platform will vary; see https://ninja-build.org/.

Alternatively, you can set -G "Makefile" in each CMake command to use
standard UNIX Makefiles, or you can substitute any other CMake-supported
generator. Your compile times may take a hit, and LLVM is already very slow
to build, so Ninja is highly recommended.

### Build LLVM-MOS

See https://github.com/llvm-mos for more information.

```console
$ cd
$ git clone https://github.com/llvm-mos/llvm-mos.git
$ cd llvm-mos
$ mkdir build
$ cd build
$ cmake -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD="MOS" \
        -DLLVM_TARGETS_TO_BUILD="" \
        -DLLVM_ENABLE_PROJECTS="clang;lld" \
        -G "Ninja" \
        ../llvm
$ ninja clang lld llvm-ar llvm-ranlib
$ alias clang-mos=$HOME/llvm-mos/build/bin/clang
```

This will place binaries in a newly-created "bin" directory. An alias will
allow easily using clang later.

### Build LLVM-MOS-SDK

Once you have a working compiler, you can use it to build the SDK itself.
You'll need to point the SDK at the compiler using -DLLVM_MOS, which requires
an absolute path to the bin directory. If you compiled the compiler somewhere else, make sure to modify the snippet below with the correct path.

```console
$ cd ../..
$ git clone https://github.com/llvm-mos/llvm-mos-sdk.git
$ cd llvm-mos-sdk
$ mkdir build
$ cd build
$ cmake -DLLVM_MOS=$HOME/llvm-mos/build/bin -G "Ninja" ..
$ ninja
```

The SDK will now be present in the build (current) directory.

Compiler flags for MOS targets in the SDK may be set using -DLLVM_MOS_ARCH_FLAGS:

```console
$ cmake -DLLVM_MOS=$HOME/llvm-mos/build/bin -DLLVM_MOS_ARCH_FLAGS=-mcpu=mos65c02 -G "Ninja" ..
```

### Compile the example

Once you have the SDK, you can compile the sample program using the alias
created earlier. You'll need to provide `--config=`, which should point to
one of the target-specific Clang configuration files (at present, there's
only `.../commodore/64.cfg`). These configuration files provide the
command-line arguments necessary to generate executables for a specific MOS
target.

```console
$ cd ..
$ clang-mos --config build/commodore/64.cfg -Os -o hello.prg examples/hello_putchar.c

$ cat examples/hello_putchar.c
#include <stdio.h>

int main(void) {
  const char *cur = "HELLO, PUTCHAR!\n";
  while (*cur)
    __putchar(*cur++);
  return 0;
}

$ hexdump -C hello.prg
00000000  01 08 0b 08 5d 1e 9e 32  30 36 31 00 00 00 a9 ff  |....]..2061.....|
00000010  85 02 a9 9f 85 03 a9 93  85 04 a9 08 85 05 a9 00  |................|
00000020  a2 00 a0 00 20 40 08 20  2c 08 4c 29 08 a2 00 a9  |.... @. ,.L)....|
00000030  48 20 d2 ff bd 83 08 e8  e0 10 d0 f5 a2 00 a9 00  |H ..............|
00000040  60 85 09 84 08 8a 05 08  c9 00 f0 36 86 0e a0 00  |`..........6....|
00000050  18 a5 0e 69 ff aa a5 08  69 ff 85 08 a5 04 18 69  |...i....i......i|
00000060  01 85 0c a5 05 69 00 85  0d a5 09 91 04 8a 86 0e  |.....i..........|
00000070  05 08 48 a5 0c 85 04 68  48 a5 0d 85 05 68 c9 00  |..H....hH....h..|
00000080  d0 ce 60 48 45 4c 4c 4f  2c 20 50 55 54 43 48 41  |..`HELLO, PUTCHA|
00000090  52 21 0a 00                                       |R!..|
00000094

$ clang-mos --config build/commodore/64.cfg -Os -o hello.s -Wl,--lto-emit-asm examples/hello_putchar.c

$ cat hello.s
        .text
        .file   "ld-temp.o"
        .section        .text.main,"ax",@progbits
        .globl  main
        .type   main,@function
main:
        ldx     #0
        lda     #72
.LBB0_1:
        sta     65529
        lda     .str+1,x
        inx
        cpx     #16
        bne     .LBB0_1
        ldx     #0
        lda     #0
        rts
.Lfunc_end0:
        .size   main, .Lfunc_end0-main

        .section        .text.exit,"ax",@progbits
        .globl  exit
        .type   exit,@function
exit:
        sta     65528
        ;APP
        ;NO_APP
.Lfunc_end1:
        .size   exit, .Lfunc_end1-exit

...Superfluous ASM...

.str:
        .asciz  "HELLO, PUTCHAR!\n"
        .size   .str, 17

```

The generated ASM output will contain more than actually ends up in the binary.
In the default MOS configuration, LLD runs a very late garbage collection pass
through the output sections to discard any functions not actually referenced.
