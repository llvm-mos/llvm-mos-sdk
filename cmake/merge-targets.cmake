define_property(TARGET PROPERTY LLVM_MOS_MERGED_TARGETS
  BRIEF_DOCS "Generator expressions for targets to merge into the resulting target."
  FULL_DOCS "Generator expressions for targets to merge into the resulting target.")

# Merge all of the provided target into the given target. The targets must
# either all be static libraries or all be object files. 
function(merge_targets tgt)
  if(NOT ARGV)
    return()
  endif()

  get_target_property(type ${tgt} TYPE)
  if(NOT type STREQUAL STATIC_LIBRARY)
    message(FATAL_ERROR "merge_targets called on unsupported target ${tgt} of type ${type}")
  endif()

  get_target_property(object_file ${tgt} LLVM_MOS_OBJECT_FILE)

  get_property(merged_set TARGET ${tgt} PROPERTY LLVM_MOS_MERGED_TARGETS SET)
  if(NOT merged_set)
    if(object_file)
      add_custom_command(TARGET ${tgt} POST_BUILD
        COMMAND ${CMAKE_LINKER} -r -o $<TARGET_OBJECTS:${tgt}> $<TARGET_OBJECTS:${tgt}>
          $<GENEX_EVAL:$<TARGET_PROPERTY:LLVM_MOS_MERGED_TARGETS>>
        COMMAND_EXPAND_LISTS)
    else()
      add_custom_command(TARGET ${tgt} POST_BUILD
        COMMAND ${CMAKE_AR} qL $<TARGET_FILE:${tgt}>
                $<GENEX_EVAL:$<TARGET_PROPERTY:LLVM_MOS_MERGED_TARGETS>>
        COMMAND_EXPAND_LISTS)
    endif()
  endif()

  add_dependencies(${tgt} ${ARGN})
  foreach(other ${ARGN})
    if(object_file)
      set_property(TARGET ${tgt}
        APPEND PROPERTY LLVM_MOS_MERGED_TARGETS $<TARGET_OBJECTS:${other}>)
    else()
      set_property(TARGET ${tgt}
        APPEND PROPERTY LLVM_MOS_MERGED_TARGETS $<TARGET_FILE:${other}>)
    endif()
  endforeach()
endfunction()
