define_property(TARGET PROPERTY MERGED_TARGETS
  BRIEF_DOCS "Generator expressions for libraries to merge into the resulting library."
  FULL_DOCS "Generator expressions for libraries to merge into the resulting library.")

# Merge all of the provided static libraries into the given static library.
function(merge_libraries target)
  if(NOT ARGV)
    return()
  endif()

  get_target_property(type ${target} TYPE)
  if(NOT type STREQUAL STATIC_LIBRARY)
    message(FATAL_ERROR "merge_libraries called on unsupported target ${target} of type ${type}")
  endif()

  get_property(merged_set TARGET ${target} PROPERTY MERGED_TARGETS SET)
  if(NOT merged_set)
    add_custom_command(TARGET ${target} POST_BUILD
      COMMAND ${CMAKE_AR} qL $<TARGET_FILE:${target}>
              $<GENEX_EVAL:$<TARGET_PROPERTY:MERGED_TARGETS>>
      COMMAND_EXPAND_LISTS)
  endif()

  target_link_libraries(${target} PUBLIC ${ARGN})
  foreach(merged ${ARGN})
    set_property(TARGET ${target}
      APPEND PROPERTY MERGED_TARGETS $<TARGET_FILE:${merged}>)
  endforeach()
endfunction()
