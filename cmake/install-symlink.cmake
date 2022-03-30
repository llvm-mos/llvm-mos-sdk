# Creates (or copies) a target file as a symlink during install.
function(install_symlink name dest)
  set(full_name ${name}${CMAKE_EXECUTABLE_SUFFIX})
  set(full_dest ${dest}${CMAKE_EXECUTABLE_SUFFIX})

  install(SCRIPT ${CMAKE_SOURCE_DIR}/cmake/install-symlink-impl.cmake
          CODE "install_symlink_impl(${full_name} ${full_dest} bin)")
endfunction()
