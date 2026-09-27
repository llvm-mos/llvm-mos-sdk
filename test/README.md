# Unit Tests

## Adding new Emutest/Libretro tests

You can write tests against any Libretro core found by CMake:

```cmake
  add_emutest_test(<name> <ext> <source_dir> <libretro_core>)
```

* name - Project suffix, also prefix of C file
* ext - Output binary/ROM file extension (ex: a26)
* source_dir - Look for {name}.c in this relative path, usually "."
* libretro_core - Variable containing path to Libretro library file

Usually these are invoked via wrapper function, see `test/test.cmake`.

To add new Libretro cores and wrapper functions to the project, search for `LIBRETRO_STELLA_CORE` and use those lines as a template for your new core.

How to report results from a test case:

* Call `test_set_result(bool)` with a pass/fail value, and then go into a busy loop or video display loop, or
* Exit from `main()` with a status code -- zero for success, non-zero for failure, or
* Set the `EMUTEST_FB_CRC_PASS` variable to the CRC of a known good video frame (you can find these in the test log files.)

## C64 and C128 tests (VICE)

`test/c128` holds the Commodore 128 tests, and `test/c64` a smaller set for the
Commodore 64. They are built and registered like the other platforms'
(`ninja test-c128`, or `ninja test` for everything). Two kinds of test:

* `add_vice_test(<name>)` - run under VICE's `x128`/`x64sc` by
  `test/vice-runner.py` and reported through the same protocol as the emutest
  tests above: the program exits with a status - returns `EXIT_SUCCESS` or
  `EXIT_FAILURE` from `main` - and `test-lib-emutest`'s `_Exit` stores
  `TestPass`/`TestFail` in the RAM array `test_result`. The runner runs the
  program through its exit handlers and `_Exit` (a program that hangs or never
  exits fails), reads `test_result` from RAM through the VICE monitor, and
  decodes it.

  `test-check.h` provides `CHECK(condition)` for such tests: a false condition
  records its line in `test_fail_line` and returns `EXIT_FAILURE`, and
  `vice-runner.py` prints that line when the test fails.

  Do not call `test_set_result()` and then `return 0`: on this platform
  returning from `main` goes through `exit()` to `_Exit(0)`, which overwrites
  the signature with `TestPass`. Return the status instead.

* `add_vice_basic_return_test(<name>)` is the other kind of emulator test: the
  program is linked with `save-basic.o` (not `test-lib-emutest`), returns to
  BASIC, and passes if BASIC's `READY.` prompt is on the screen afterwards. It
  runs under VICE only.

VICE is found through the `VICE_DIR` environment variable (its install
directory) or `-DVICE_X128_COMMAND=<path to x128>` /
`-DVICE_X64SC_COMMAND=<path to x64sc>`. Without it the emulator
tests are not registered, but the programs are still built. The tests need
Python 3 for the runner and open an emulator window; CTest runs them one at a
time.

Each emulator test can also run headlessly under `emutest` with the libretro
VICE core (`vice-libretro`, targets `x128` and `x64sc`), registered as
`test-<name>-libretro` when `EMUTEST_COMMAND` and the core are found
(`LIBRETRO_CORES_DIR` names the directory holding `vice_x128_libretro` and
`vice_x64sc_libretro` with extension `.so`/`.dylib`/`.dll`). That path takes a
fraction of a second per test, but it can only check the pass/fail signature:
the Common-RAM restore check needs the monitor breakpoints of `vice-runner.py`.

```cmake
  add_vice_test(<name>)                 # <name>.c
  add_vice_test(<name> SOURCE other.c   # same source, different link options
    LINK_OPTIONS -Wl,--defsym=...
    RESTORE_RANGE 0c00-0dff)            # Common-RAM code area (see below)
  add_vice_test(<name> EXTRA_SOURCES more.s)   # further sources (e.g. assembly)
```

On the c128, if the program links code that borrows the shared "Common-RAM
code area" while switching to another RAM bank (detected by an `.init.011`
section in the link), the runner also checks that area is restored at exit:
it dumps `$0800-$09FF` (or `RESTORE_RANGE`) before the platform first
overwrites it and again after the exit handlers, and the two must be
identical (see `vice-runner.py`'s own docstring for the exact mechanism).
No test in this directory currently triggers this check.

Run `vice-runner.py` directly for one program (`--vice`, `--prg`, `--map`; the
map is written by `-Wl,-Map=`); its exit status is 0 for pass, 1 for fail and 2
for no result.
