# Examples

This directory provides the means to build executables for all platforms
implemented in the SDK. CMake visits this directory for each platform. Binaries
are output in `mos-build/examples/<platform>`. Any targets added with
`llvm_mos_sdk_add_example_executable` will have runtime dependencies
automatically established for each respective platform. The host project will
have a `run-<target>` target created which will run the simulator on the sim
platform's binary automatically.

If a subdirectory named after a specific platform is created here, it will only
be visited by CMake for that platform. This way, platform specific targets (also
using `llvm_mos_sdk_add_example_executable`) can be easily established.

Beyond just examples, this directory may be used as a "playground" for
iterating on runtime libraries as all necessary build and link dependencies
are in place.
