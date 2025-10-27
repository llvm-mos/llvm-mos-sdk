# LLVM-MOS SDK

The LLVM-MOS compiler toolchain and platform libraries.

[API Reference](https://llvm-mos.github.io/llvm-mos-sdk/files.html)

## Supported platforms

- [Atari 2600](https://en.wikipedia.org/wiki/Atari_2600)
  - 4K cartridge
  - [TigerVision 3E (2-KiB fixed, 2-KiB banked ROM or RAM)](https://www.taswegian.com/WoodgrainWizard/tiki-index.php?page=3E)
- [Atari 5200](https://en.wikipedia.org/wiki/Atari_5200) Super Cart from [32 KiB](https://github.com/atari800/atari800/blob/ATARI800_5_2_0/DOC/cart.txt#L105)
  to [512 KiB](https://github.com/atari800/atari800/blob/ATARI800_5_2_0/DOC/cart.txt#L108)
- [Atari 8-bit](https://en.wikipedia.org/wiki/Atari_8-bit_family)
  - [DOS](https://en.wikipedia.org/wiki/Atari_DOS) ".XEX" file
  - Standard cartridge ([8 KiB](https://github.com/atari800/atari800/blob/ATARI800_5_2_0/DOC/cart.txt#L35)
    or [16 KiB](https://github.com/atari800/atari800/blob/ATARI800_5_2_0/DOC/cart.txt#L36))
  - XEGS (lower 8 KiB bank-switched) cartridge from [32 KiB](https://github.com/atari800/atari800/blob/ATARI800_5_2_0/DOC/cart.txt#L46) to
    [512 KiB](https://github.com/atari800/atari800/blob/ATARI800_5_2_0/DOC/cart.txt#L58)
	- Compatible with [S/XEGS (switchable XEGS)](https://github.com/atari800/atari800/blob/ATARI800_5_2_0/DOC/cart.txt#L67)
  - MegaCart (16 KiB fully-banked) cartridge from [16 KiB](https://github.com/atari800/atari800/blob/ATARI800_5_2_0/DOC/cart.txt#L60)
    to [512 KiB](https://github.com/atari800/atari800/blob/ATARI800_5_2_0/DOC/cart.txt#L65)
	- Compatible with SIC! [128 KiB](https://github.com/atari800/atari800/blob/ATARI800_5_2_0/DOC/cart.txt#L88) to
	  [512 KiB](https://github.com/atari800/atari800/blob/ATARI800_5_2_0/DOC/cart.txt#L90)
- [Atari Lynx](https://en.wikipedia.org/wiki/Atari_Lynx)
  - BLL format ".o" executable file
- [Ben Eater's Breadboard 6502 Computer](https://eater.net/6502)
- [Commander X16](https://www.commanderx16.com/)
- [Commodore 64](https://en.wikipedia.org/wiki/Commodore_64)
- [Commodore 128](https://en.wikipedia.org/wiki/Commodore_128)
- [Commodore PET](https://en.wikipedia.org/wiki/Commodore_PET)
- [Commodore VIC-20](https://en.wikipedia.org/wiki/VIC-20)
- [CP/M-65](https://github.com/davidgiven/cpm65)
- [Dodo 6502 Game System](https://github.com/peternoyes/dodo)
- [Commodore GEOS](https://en.wikipedia.org/wiki/GEOS_(8-bit_operating_system))
- [MEGA65](https://mega65.org/)
- [NES (Nintendo Entertainment System)](https://en.wikipedia.org/wiki/Nintendo_Entertainment_System)
  - [Action 53](https://www.nesdev.org/wiki/Action_53)
  - [CNROM](https://www.nesdev.org/wiki/CNROM)
  - [GTROM](https://www.nesdev.org/wiki/GTROM)
  - [NROM](https://www.nesdev.org/wiki/NROM)
  - [UNROM](https://www.nesdev.org/wiki/UxROM)
  - [UNROM-512](https://www.nesdev.org/wiki/UNROM_512)
  - [MMC1](https://www.nesdev.org/wiki/MMC1)
  - [MMC3](https://www.nesdev.org/wiki/MMC3)
  - [Family Computer Disk System](https://www.nesdev.org/wiki/Family_Computer_Disk_System)
- [Ohio Scientific Challenger 1P](https://en.wikipedia.org/wiki/Ohio_Scientific#Superboard_II,_Challenger_1P_(1978))
- [OLIMEX Neo6502](https://www.olimex.com/Products/Retro-Computers/Neo6502/open-source-hardware)
- [Picocomputer 6502](https://picocomputer.github.io) (RP6502)
- [PC Engine / TurboGrafx-16](https://en.wikipedia.org/wiki/TurboGrafx-16)
  - [PC Engine CD](https://en.wikipedia.org/wiki/TurboGrafx-16#TurboGrafx-CD/CD-ROM%C2%B2)
- [RPC/8e](http://www.eloraam.com/blog/2012/04/22/rp-control-internals/) (RedPower 2)
- 6502 simulator (included)

## Notable features

- Broad C99 and C++11 freestanding standards compatibility
- The high and low-level optimizations expected of a young-ish LLVM backend
  - Fairly good register allocation over A, X, Y, and a field of 16 2-byte zero-page (imaginary) registers
  - The imaginary registers can be placed anywhere and need not be contiguous.
  - The calling convention passes through registers whenever possible.
  - Loop optimizations to select 6502 addressing modes
  - Whole program "static stack" optimization
    - Automatically identifies non-reentrant functions and allocates their frames as static globals
    - Programs without recursion or complex function pointers may not need a soft stack at all.
    - No manual annotations required
  - Whole program zero page allocation
  - Link time inlining and optimization across the whole program
    - Includes SDK libraries. Library calls can be often optimized away completely!
- Excellent compiler usability
  - Clang's world-class error messages
  - IDE integration through the included custom clangd's Language Server Protocol
  - Straightforward invocations to compile for various targets: `mos-c64-clang++ -Os -o game.prg game.cc`
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

- A hosted C with all the standard library bells and whistles.
- C++ Exceptions


## Getting started

### Download

First, download and extract the archive for your platform.

- [Linux](https://github.com/llvm-mos/llvm-mos-sdk/releases/latest/download/llvm-mos-linux.tar.xz)
- [Mac OS](https://github.com/llvm-mos/llvm-mos-sdk/releases/latest/download/llvm-mos-macos.tar.xz)
- [Windows](https://github.com/llvm-mos/llvm-mos-sdk/releases/latest/download/llvm-mos-windows.7z)

### (macOS Only) Remove Quarantine

On macOS, downloading a package automatically applies a quarantine to the file.
This will also affect the extracted binaries from the package, which causes
GateKeeper to prevent them from running. To avoid this, run the following on the
downloaded package before extracting it:

```shell
$ xattr -d com.apple.quarantine llvm-mos-macos.tar.xz
```

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

| Platform                        | Variant            | Command                          |
|---------------------------------|--------------------|----------------------------------|
| Atari 2600                      | 4K                 | `mos-atari2600-4k-clang`         |
| Atari 2600                      | TigerVision 3E     | `mos-atari2600-3e-clang`         |
| Atari 5200                      | Super Cart         | `mos-atari5200-supercart-clang`  |
| Atari 8-bit                     | DOS                | `mos-atari8-dos-clang`           |
| Atari 8-bit                     | MegaCart cartridge | `mos-atari8-cart-megacart-clang` |
| Atari 8-bit                     | Standard cartridge | `mos-atari8-cart-std-clang`      |
| Atari 8-bit                     | XEGS cartridge     | `mos-atari8-cart-xegs-clang`     |
| Atari Lynx                      | BLL executable     | `mos-lynx-bll-clang`             |
| Ben Eater's 6502 Breadboard Kit | -                  | `mos-eater-clang`                |
| Commander X16                   | -                  | `mos-cx16-clang`                 |
| Commodore                       | 64                 | `mos-c64-clang`                  |
| Commodore                       | 128                | `mos-c128-clang`                 |
| Commodore                       | PET                | `mos-pet-clang`                  |
| Commodore                       | VIC-20             | `mos-vic20-clang`                |
| CP/M-65                         | -                  | `mos-cpm65-clang`                |
| Dodo 6502 Game System           | -                  | `mos-dodo-clang`                 |
| Commodore GEOS                  | 64, 128            | `mos-geos-cbm-clang`              |
| MEGA65                          | -                  | `mos-mega65-clang`               |
| NES                             | Action53 mapper    | `mos-nes-action53-clang`         |
| NES                             | CNROM mapper       | `mos-nes-cnrom-clang`            |
| NES                             | GTROM mapper       | `mos-nes-gtrom-clang`            |
| NES                             | MMC1 mapper        | `mos-nes-mmc1-clang`             |
| NES                             | MMC3 mapper        | `mos-nes-mmc3-clang`             |
| NES                             | NROM mapper        | `mos-nes-nrom-clang`             |
| NES                             | UNROM mapper       | `mos-nes-unrom-clang`            |
| NES                             | UNROM-512 mapper   | `mos-nes-unrom-512-clang`        |
| Ohio Scientific Challenger 1P   | -                  | `mos-osi-c1p-clang`              |
| OLIMEX Neo6502                  | -                  | `mos-neo6502-clang`              |
| Picocomputer 6502               | -                  | `mos-rp6502-clang`               |
| PC Engine                       | Standard           | `mos-pce-clang`                  |
| PC Engine                       | CD                 | `mos-pce-cd-clang`               |
| RPC/8e (RedPower 2)             | -                  | `mos-rpc8e-clang`                |
| Watara Supervision              | -                  | `mos-supervision-clang`          |
| 6502 simulator                  | -                  | `mos-sim-clang`                  |


```console
$ cat <install_dir>/examples/hello-putchar.c
#include <stdio.h>

int main(void) {
  const char *cur = "HELLO, PUTCHAR!\n";
  while (*cur)
    putchar(*cur++);
  return 0;
}

$ mos-c64-clang -Os -o hello.prg <install_dir>/examples/hello-putchar.c

$ llvm-objdump -d hello.elf
...

$ mos-c64-clang -Os -o hello.s -Wl,--lto-emit-asm <install_dir>/examples/hello-putchar.c
```

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

### Install a working host compiler and CMake

The SDK builds with CMake and builds binaries that are intended to run on your host operating system (in addition to the libraries for the 6502).
Accordingly, to build the SDK, you'll need to install a working CMake and host OS C/C++ compiler, such that CMake is able to build binaries.

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

### Run Unit Tests

#### NES (legacy Mesen Mono version tests)

Install [Mesen-X](https://github.com/NovaSquirrel/Mesen-X/releases) and its dependencies.

Set the `MESEN_DIR` environment variable to the folder containing the Mesen.exe executable before running CMake for the first time.
Copy `test/mesen_settings.xml` to this folder.

#### Libretro tests (Atari 2600, etc.)

Install emutest (requires Go 1.21):
```console
$ go install github.com/kivutar/emutest@latest
```

Make sure `$GOBIN` (usually `~/go/bin`) is included in your `PATH`
environment variable so that CMake can find the binary, or set the
`EMUTEST_DIR` environment variable to point to this directory before
running `cmake -G` for the first time.

You can verify emutest with `emutest -h` on the command-line.

You should see `-T Test runner mode (script must call os.exit)` in the
output.

Build Libretro cores for desired target(s):

* Atari 2600 - https://github.com/libretro/stella2014-libretro
* NES - https://github.com/NovaSquirrel/Mesen-X

Copy the output Libretro core library files (they have extensions .so | .dylib | .dll) to a shared directory, maybe `$HOME/libretro`.
Set the `LIBRETRO_CORES_DIR` environment variable to this folder before running `cmake -G` for the first time.

#### Run a test project

```console
$ ninja test            # run all test projects
$ ninja test-nes-nrom   # run a specific test project, e.g. nes-nrom
```
