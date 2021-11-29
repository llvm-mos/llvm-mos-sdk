function(compile_for_mos)

include_directories(${CMAKE_SOURCE_DIR}/common/include)

set(CMAKE_ASM_COMPILER "${LLVM_MOS}/clang" PARENT_SCOPE)
set(CMAKE_C_COMPILER "${LLVM_MOS}/clang" PARENT_SCOPE)
set(CMAKE_CXX_COMPILER "${LLVM_MOS}/clang" PARENT_SCOPE)
set(CMAKE_AR "${LLVM_MOS}/llvm-ar" PARENT_SCOPE)
set(CMAKE_RANLIB "${LLVM_MOS}/llvm-ranlib" PARENT_SCOPE)

set(CMAKE_ASM_FLAGS "--target=mos ${LLVM_MOS_ARCH_FLAGS}" PARENT_SCOPE)
set(CMAKE_C_FLAGS "--target=mos ${LLVM_MOS_ARCH_FLAGS} -flto -Os" PARENT_SCOPE)
set(CMAKE_CXX_FLAGS "--target=mos ${LLVM_MOS_ARCH_FLAGS} -flto -Os" PARENT_SCOPE)
endfunction()
