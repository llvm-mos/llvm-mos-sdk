# Simple, recursive ldscript parser to extract linker script paths.
# CMake uses this information to set up in-tree build dependencies.
# ldscript search paths are provided via variadic args.
function(read_linker_script_deps ld_file ld_list_var)
  if(${ld_file} IN_LIST ${ld_list_var})
    return()
  endif()
  list(APPEND ${ld_list_var} ${ld_file})
  file(STRINGS ${ld_file} ld_file_lines)
  foreach(line ${ld_file_lines})
    if(line MATCHES "[ \t]*INCLUDE[ \t]+([^ \t\r\n]+)")
      # Handle ldscript file include
      set(match ${CMAKE_MATCH_1})
      if(NOT IS_ABSOLUTE ${match})
        foreach(search_path ${ARGN})
          if(EXISTS ${search_path}/${match})
            set(match ${search_path}/${match})
            break()
          endif()
        endforeach()
      endif()
      get_filename_component(match ${match} ABSOLUTE)
      # CMake has a default recursion limit of 400.
      # This should be plenty to accommodate the imag_reg scripts.
      if(EXISTS ${match})
        read_linker_script_deps(${match} ${ld_list_var} ${ARGN})
      endif()
    endif()
  endforeach()
  set(${ld_list_var} ${${ld_list_var}} PARENT_SCOPE)
endfunction()
