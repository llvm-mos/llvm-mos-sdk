# Based on LLVMInstallSymlink.cmake

function(create_symlink name target outdir)
  execute_process(
          COMMAND "${CMAKE_COMMAND}" -E create_symlink "${target}" "${name}"
          WORKING_DIRECTORY "${outdir}" ERROR_VARIABLE has_err)
  if(CMAKE_HOST_WIN32 AND has_err)
    execute_process(
            COMMAND "${CMAKE_COMMAND}" -E copy "${target}" "${name}"
            WORKING_DIRECTORY "${outdir}")
  endif()
endfunction()

create_symlink(${NAME} ${TARGET} ${OUTDIR})
