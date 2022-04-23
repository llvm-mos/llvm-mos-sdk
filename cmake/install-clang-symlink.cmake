# Creates a symlink to clang that causes the config file for a given platform to
# be used automatically.
function(install_clang_symlink bindir platform suffix)
  set(file mos-${platform}-${suffix})
  message(STATUS "Creating symlink ${file}")

  execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink mos-${suffix} ${file}
    WORKING_DIRECTORY ${bindir})
endfunction()
