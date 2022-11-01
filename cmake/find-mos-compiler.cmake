function(find_mos_compiler compiler_var bin_name)
  function(_find_mos_compiler_impl out_var)
    # Do not find if variable already set.
    if(${compiler_var})
      set(${out_var} ${${compiler_var}} PARENT_SCOPE)
      return()
    endif()

    # Return if find_program succeeded.
    macro(return_found_bin)
      if(found_bin)
        set(${out_var} ${found_bin} PARENT_SCOPE)
        unset(found_bin CACHE)
        return()
      endif()
    endmacro()

    # First attempt finding clang at LLVM_MOS if provided.
    if(LLVM_MOS)
      find_program(found_bin ${bin_name} PATHS ${LLVM_MOS} ${LLVM_MOS}/bin NO_CACHE NO_DEFAULT_PATH)
      return_found_bin()
    endif()

    # Next attempt finding clang at CMAKE_INSTALL_PREFIX if provided (typically for bootstrapping SDK).
    if(CMAKE_INSTALL_PREFIX)
      find_program(found_bin ${bin_name} PATHS ${CMAKE_INSTALL_PREFIX}/bin NO_CACHE NO_DEFAULT_PATH)
      return_found_bin()
    endif()

    # In case this list file is installed, attempt relative search.
    set(rel_bin_dir ${CMAKE_CURRENT_LIST_DIR}/../../../bin)
    if(EXISTS ${rel_bin_dir})
      find_program(found_bin ${bin_name} PATHS ${rel_bin_dir} NO_CACHE NO_DEFAULT_PATH)
      return_found_bin()
    endif()

    # If we are on windows, try and find the program as a batch script first
    # By default, cmake doesn't consider `.bat` as an executable extension, but it will find it
    # if we specify the name of the file exactly
    if(WIN32)
      find_program(found_bin ${bin_name}.bat NO_CACHE)
      return_found_bin()
    endif()

    # Finally attempt finding clang with cmake's default find logic.
    find_program(found_bin ${bin_name} NO_CACHE)
    set(${out_var} ${found_bin} PARENT_SCOPE)
    unset(found_bin CACHE)
  endfunction()

  _find_mos_compiler_impl(clang_bin)
  if(NOT clang_bin)
    return()
  endif()

  # If we found clang, check that it is capable of targeting MOS.
  execute_process(COMMAND ${CMAKE_COMMAND} -E echo "int main() {}"
          COMMAND ${clang_bin} --target=mos -S -xc -o - -
          RESULT_VARIABLE clang_result
          OUTPUT_QUIET)
  if(NOT clang_result STREQUAL 0)
    message(FATAL_ERROR "Unable to target MOS using ${clang_bin}. "
            "Try setting LLVM_MOS to a directory containing LLVM-MOS clang binary.")
  endif()

  # If we get here without a fatal error, the compiler is valid.
  set(${compiler_var} ${clang_bin} PARENT_SCOPE)
endfunction()
