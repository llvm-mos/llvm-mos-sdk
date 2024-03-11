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
