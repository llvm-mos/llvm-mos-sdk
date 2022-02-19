# If the LLVM_MOS_BOOTSTRAP_COMPILER variable is enabled, then attempt to
# download it and use it.

if(LLVM_MOS_BOOTSTRAP_COMPILER)
  if(NOT LLVM_MOS_PRECOMPILED_TOOLS)
    string(TOLOWER ${CMAKE_HOST_SYSTEM_NAME} _cmake_host_system_name_lowercase)
    set(LLVM_MOS_PRECOMPILED_TOOLS llvm-mos-${_cmake_host_system_name_lowercase}-main
            CACHE STRING "The name of the llvm-mos release to download for precompiled tools")
  endif()
  if (WIN32)
    set(extension zip)
  else()
    set(extension tar.xz)
  endif()
  include(FetchContent)
  FetchContent_Declare(
          llvm-mos
          URL https://github.com/llvm-mos/llvm-mos/releases/download/${LLVM_MOS_PRECOMPILED_TOOLS}/${LLVM_MOS_PRECOMPILED_TOOLS}.${extension}
  )
  message("-- Downloading LLVM-MOS compiler, please wait...")
  FetchContent_MakeAvailable(llvm-mos)
  if (llvm-mos_POPULATED)
    message("-- LLVM-MOS compiler downloaded")
  else()
    message(SEND_ERROR "Could not download LLVM-MOS compiler; please try again or build it yourself")
  endif()
endif()
