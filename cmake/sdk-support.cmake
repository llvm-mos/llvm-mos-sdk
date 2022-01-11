# Sets `var` to a relative path based on the current CMakeLists.txt directory.
# Helps to make an install structure that reflects the repository structure.
function(_get_relative_install_path var)
  file(RELATIVE_PATH install_path ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
  if(NOT install_path)
    set(install_path .)
  endif()
  set(${var} ${install_path} PARENT_SCOPE)
endfunction()

# Adds to the install target with the install directory based on the current
# CMakeLists.txt location.
function(llvm_mos_sdk_install)
  _get_relative_install_path(path)
  install(${ARGN} DESTINATION ${path})
endfunction()

# All platform object files depend on platform config files.
function(_target_depend_config_files name)
  get_target_property(sources ${name} SOURCES)
  set_source_files_properties(${sources} PROPERTIES OBJECT_DEPENDS
    "${LLVM_MOS_CURRENT_PLATFORM_CONFIG_FILES}")
endfunction()

# Runtime targets (i.e. crt,c,m) are tracked per-platform. When example
# executable targets are created, these tracked targets are automatically
# set up as target dependencies with no installation necessary.
#
# Platforms themselves do not have to use this. It is primarily used in
# specialization functions that the common "platform" defines.
function(llvm_mos_sdk_track_platform_target name)
  set_property(GLOBAL APPEND PROPERTY LLVM_MOS_CURRENT_PLATFORM_TARGETS ${name})
  _target_depend_config_files(${name})
endfunction()

# Creates a single-source platform target that is installed as a .o file.
function(llvm_mos_sdk_add_object_file name src)
  if(NOT LLVM_MOS_CURRENT_PLATFORM)
    message(FATAL_ERROR "llvm_mos_sdk_add_object_file() can only be used in "
            "llvm_mos_sdk_add_platform() scope")
  endif()
  set(target_name ${LLVM_MOS_CURRENT_PLATFORM}-${name})

  if(ARGC GREATER 2)
    set(outname ${ARGV2})
  else()
    set(outname ${name}.o)
  endif()

  # Even though we just need the object file, build a full static library
  # so POST_BUILD hook works (just ignore the .a, it won't be installed).
  add_library(${target_name} STATIC ${src})
  _get_relative_install_path(lib_path)
  install(FILES $<TARGET_OBJECTS:${target_name}> DESTINATION ${lib_path} RENAME ${outname})
  llvm_mos_sdk_track_platform_target(${target_name})

  # Create symlink (or copy) to the object file on each build. Since CMake
  # does not allow us to customize the output location of our one-and-only
  # object file, this is necessary to place the object in the normal library
  # search path for examples to link with.
  add_custom_command(TARGET ${target_name} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS
    -DNAME=${outname} -DTARGET=$<TARGET_OBJECTS:${target_name}> -DOUTDIR=${CMAKE_CURRENT_BINARY_DIR}
    -P ${CMAKE_SOURCE_DIR}/cmake/create-symlink.cmake DEPENDS $<TARGET_OBJECTS:${target_name}>)
endfunction()

# Creates (or copies) a target file as a symlink during install.
function(llvm_mos_sdk_install_symlink name dest)
  set(full_name ${name}${CMAKE_EXECUTABLE_SUFFIX})
  set(full_dest ${dest}${CMAKE_EXECUTABLE_SUFFIX})

  install(SCRIPT ${CMAKE_SOURCE_DIR}/cmake/install-symlink.cmake
          CODE "install_symlink(${full_name} ${full_dest} bin)")
endfunction()

# Extends the SDK structure with a new platform.
# This may only be called from the mos-platform directory.
#
# At minimum, a platform consists of a clang configuration file named
# mos-<name>.cfg. If a subdirectory <name> exists, it will automatically
# be added as a CMake subdirectory with LLVM_MOS_CURRENT_PLATFORM set to
# <name> and compiler flags set to use the configuration file. Platforms
# can then use the support functions provided here and in
# mos-platform/common/lib/CMakeLists.txt to specialize platform runtime
# libraries and other artifacts.
#
# This function is called on both MOS and host projects. The host project
# uses this to visit platforms in order to create clang symlinks with the
# host's CMAKE_EXECUTABLE_SUFFIX (so Windows symlinks end in .exe) and
# so examples create run-<name> simulator targets.
function(llvm_mos_sdk_add_platform name)
  cmake_parse_arguments(ARG BUILD_EXAMPLES "" "" ${ARGN})
  set(cfg_file mos-${name}.cfg)

  _get_relative_install_path(rel_path)
  if(NOT rel_path STREQUAL mos-platform)
    message(FATAL_ERROR "llvm_mos_sdk_add_platform may only be called from mos-platform directory.")
  endif()

  if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${cfg_file})
    message(FATAL_ERROR "${cfg_file} does not exist for llvm_mos_sdk_add_platform.")
  endif()

  # Everything from this scope down can identify which platform is active.
  set(LLVM_MOS_CURRENT_PLATFORM ${name})

  if(NOT MOS)
    # Clang searches for config files next to itself as a last resort.
    # If the --config flag is not set, argv0 of the form <config>-clang
    # sets the implicit config file as <config>.cfg. We leverage this
    # convention using a set of symlinks for each MOS platform.
    install(FILES ${cfg_file} DESTINATION bin)
    foreach(suffix clang clang++ clang-cpp)
      llvm_mos_sdk_install_symlink(mos-${name}-${suffix} mos-${suffix})
    endforeach()
  else()
    # These flags will only be in scope for the add_subdirectory.
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --config ${CMAKE_CURRENT_SOURCE_DIR}/${cfg_file}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --config ${CMAKE_CURRENT_SOURCE_DIR}/${cfg_file}")
    set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} --config ${CMAKE_CURRENT_SOURCE_DIR}/${cfg_file}")

    # Tracks all added targets for platform.
    set_property(GLOBAL PROPERTY LLVM_MOS_CURRENT_PLATFORM_TARGETS "")

    # Gather config and linker script files from root cfg.
    # Config files are set as object file dependencies for libraries and examples.
    # Linker scripts are set as example executable dependencies.
    include(read-config-deps)
    include(read-linker-script-deps)
    set(cfg_file_abs ${CMAKE_CURRENT_SOURCE_DIR}/${cfg_file})
    read_config_deps(${cfg_file_abs} LLVM_MOS_CURRENT_PLATFORM_CONFIG_FILES ld_list link_dir_list)
    foreach(ld ${ld_list})
      read_linker_script_deps(${ld} LLVM_MOS_CURRENT_PLATFORM_LDSCRIPT_FILES ${link_dir_list})
    endforeach()
    unset(platform_link_dirs)
    foreach(link_dir ${link_dir_list})
      if (link_dir MATCHES "^${CMAKE_CURRENT_SOURCE_DIR}/")
        # In-tree linking requires source -> binary search path translation.
        file(RELATIVE_PATH link_dir ${CMAKE_CURRENT_SOURCE_DIR} ${link_dir})
        list(APPEND platform_link_dirs ${CMAKE_CURRENT_BINARY_DIR}/${link_dir})
      endif()
    endforeach()

    # Add optional platform artifact directory.
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${name}/)
      add_subdirectory(${name})
    endif()
  endif()

  # This is done for both MOS and host so examples can have "run" targets created.
  if (LLVM_MOS_BUILD_EXAMPLES AND ARG_BUILD_EXAMPLES)
    # Normally this is set via the config file, but is required
    # here so examples can link without install.
    if(MOS)
      # link_directories() cannot be used here because it is not scoped.
      set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY
        LINK_DIRECTORIES "${platform_link_dirs}")
    endif()

    # For llvm_mos_sdk_add_example_executable to ensure it is in the correct scope.
    set(LLVM_MOS_EXAMPLES_SCOPE On)

    # Common examples directory.
    add_subdirectory(${CMAKE_SOURCE_DIR}/examples ${CMAKE_BINARY_DIR}/examples/${name})

    # Add optional per-platform examples directory.
    if(EXISTS ${CMAKE_SOURCE_DIR}/examples/${name}/)
      add_subdirectory(${CMAKE_SOURCE_DIR}/examples/${name}
                       ${CMAKE_BINARY_DIR}/examples/${name}/platform)
    endif()
  endif()
endfunction()

# Creates an executable target for MOS and a simulator run target for host.
# This may only be called from the examples directory. See examples/README.md
# for details about the functionality of the examples directory.
function(llvm_mos_sdk_add_example_executable name)
  if(NOT LLVM_MOS_CURRENT_PLATFORM)
    message(FATAL_ERROR "llvm_mos_sdk_add_example_executable() can only be used in "
            "llvm_mos_sdk_add_platform() scope")
  endif()
  if(NOT LLVM_MOS_EXAMPLES_SCOPE)
    message(FATAL_ERROR "llvm_mos_sdk_add_example_executable() can only be used in "
            "the examples directory within llvm_mos_sdk_add_platform() scope")
  endif()
  set(target_name ${LLVM_MOS_CURRENT_PLATFORM}-${name})
  if(MOS)
    # Create MOS target.
    add_executable(${target_name} ${ARGN})
    get_property(dependencies GLOBAL PROPERTY LLVM_MOS_CURRENT_PLATFORM_TARGETS)
    add_dependencies(${target_name} ${dependencies})
    set_target_properties(${target_name} PROPERTIES LINK_DEPENDS
      "${dependencies};${LLVM_MOS_CURRENT_PLATFORM_LDSCRIPT_FILES}")
    _target_depend_config_files(${target_name})
  elseif(LLVM_MOS_CURRENT_PLATFORM STREQUAL sim)
    # Create simulator "run" target.
    file(RELATIVE_PATH bin_rel_path ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${target_name})
    add_custom_target(run-${name}
      COMMAND $<TARGET_FILE:mos-sim> ${CMAKE_BINARY_DIR}/mos-build/${bin_rel_path}
      DEPENDS mos-build mos-sim
      USES_TERMINAL
    )
    set_target_properties(run-${name} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD ON)
  endif()
endfunction()
