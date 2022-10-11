# This file is part of the llvm-mos-sdk project and is redistributable under the
# terms of the Apache 2.0 license with the LLVM exceptions. See the LICENSE file
# in the project root for the full text.

add_executable(elftocpm65 elftocpm65.cc)
set_property(TARGET elftocpm65 PROPERTY CXX_STANDARD 11)
install(TARGETS elftocpm65)

