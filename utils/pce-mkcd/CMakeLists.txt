# This file is part of the llvm-mos-sdk project and is redistributable under the
# terms of the Apache 2.0 license with the LLVM exceptions. See the LICENSE file
# in the project root for the full text.

add_executable(pce-mkcd pce-mkcd.cc)
set_property(TARGET pce-mkcd PROPERTY CXX_STANDARD 17)
install(TARGETS pce-mkcd)

