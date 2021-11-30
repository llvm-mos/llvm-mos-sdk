# LLVM-MOS SDK

A WIP SDK for developing with the llvm-mos compiler.

## Project Status

At present, only one configuration for the Commodore 64 is supported, but
effort is being made to ensure that the SDK generalizes. Before the first
official release, several other first-class targets will be created to
provide examples to aid our users to port to other platforms.

A hello world example application can be built for the C64, but much of the
expected runtime is missing. As the compiler approaches C99 compatibility,
this will fill out to become a full freestanding C99 implementation.

A 6502/65C02 interpreting simulator is also provided in this repository.
Its primary use-case is testing with the LLVM-MOS fork of
[llvm-test-suite](https://github.com/llvm-mos/llvm-test-suite/).

## Build

Building the SDK first requires a working LLVM-MOS compiler. There isn't an
official release yet, but if you're eager to try it out, you can compile it yourself.

### Note for Windows users

It is recommended to [enable Developer Mode in Settings](ms-settings:developers)
so that symlinks work correctly during the installation process.

Microsoft officially deploys CMake and Ninja as part of Visual Studio if
"C++ CMake tools for Windows" enabled in the Visual Studio Installer.
If this is installed, the following steps may be performed from an
"x64 Native Tools Command Prompt" in the Start Menu.

### Install ninja

For the steps below to work as-is, you'll need to install Ninja, the fast,
parallel build tool favored by LLVM developers. Instructions for your
platform will vary; see https://ninja-build.org/.

Alternatively, you can set -G "Makefile" in each CMake command to use
standard UNIX Makefiles, or you can substitute any other CMake-supported
generator. Your compile times may take a hit, and LLVM is already very slow
to build, so Ninja is highly recommended.

### [Optional] Build and Install LLVM-MOS

**Note:** LLVM-MOS-SDK will automatically download a binary release of
LLVM-MOS from GitHub if it cannot be found on your system or if
`-DLLVM_MOS_BOOTSTRAP_COMPILER=On`. The following section is only necessary if
you wish to use your own build of llvm-mos or are using a host platform that
is not Linux|MacOS|Windows.

Installing LLVM-MOS and LLVM-MOS-SDK into the same prefix is necessary to
establish a complete cross-compilation environment. This prefix does not
have to be a system location; any user-accessible directory is fine.

**Note:** It is *not* recommended to install LLVM-MOS where it may conflict
with a vanilla LLVM/Clang installation.

See https://github.com/llvm-mos for more information.

```console
$ cd
$ git clone https://github.com/llvm-mos/llvm-mos.git
$ cd llvm-mos
$ mkdir build
$ cd build
$ cmake -C ../clang/cmake/caches/MOS.cmake \
        -G "Ninja" \
        -DCMAKE_INSTALL_PREFIX=<arbitrary-install-directory> \
        ../llvm
$ ninja install
```

This will build and install a MOS-enabled clang toolchain into the provided
prefix directory.

### Build and Install LLVM-MOS-SDK

Now it is time to build the SDK itself. If you manually built and installed
LLVM-MOS, ensure that `CMAKE_INSTALL_PREFIX` is the same as LLVM-MOS and the
compiler will be located automatically. If you wish to use another LLVM-MOS
compiler, point to it using `-DLLVM_MOS=<llvm-mos-bin-directory>`. By default,
the latest LLVM-MOS release will be downloaded from GitHub. To force
downloading from GitHub, set `-DLLVM_MOS_BOOTSTRAP_COMPILER=On`. A downloaded
LLVM-MOS is automatically installed into the LLVM-MOS-SDK prefix.

```console
$ cd ../..
$ git clone https://github.com/llvm-mos/llvm-mos-sdk.git
$ cd llvm-mos-sdk
$ mkdir build
$ cd build
$ cmake -G "Ninja" -DCMAKE_INSTALL_PREFIX=<arbitrary-install-directory> ..
$ ninja install
```

The complete SDK will now be present in the install prefix.

### [Optional] Add LLVM-MOS to PATH

This will make accessing LLVM-MOS from the command line easier:

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

### Compile the Example

**Note:** LLVM-MOS-SDK will compile the examples for each platform on its own,
but this effectively demonstrates compiler usage.

Assuming you have added LLVM-MOS to PATH, you can compile the sample program
with a direct command. You will need to prefix `clang` (or `clang++`) with a
specific MOS platform provided by the SDK. This will ensure clang loads the
correct configuration to generate executables and libraries for that target.

Current platform `clang` commands are:

* `mos-a800xl-clang`
* `mos-c64-clang`
* `mos-sim-clang`

```console
$ cd ..
$ mos-c64-clang -Os -o hello.prg examples/hello-putchar.c

$ cat examples/hello-putchar.c
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

$ mos-c64-clang -Os -o hello.s -Wl,--lto-emit-asm examples/hello-putchar.c

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

### Developing with CMake

A CMake package and toolchain file are provided to make targeting MOS from
CMake easy.

Create a new source directory with a `CMakeLists.txt` like the following where
`LLVM_MOS_PLATFORM` is set to any platform supported by the SDK:

```cmake
cmake_minimum_required(VERSION 3.13)
set(LLVM_MOS_PLATFORM c64)
find_package(llvm-mos-sdk REQUIRED)
project(llvm-mos-sdk-foo)
add_executable(foo foo.c)
```

**Note:** If LLVM-MOS was *not* added to PATH, set
`-DCMAKE_PREFIX_PATH=<arbitrary-install-directory>` to match the install prefix
of LLVM-MOS so `find_package` will work correctly.
