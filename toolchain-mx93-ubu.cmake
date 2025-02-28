SET (CMAKE_CXX_STANDARD 20)
SET (CMAKE_CXX_STANDARD_REQUIRED on)

set (CMAKE_SYSTEM_NAME Linux)
set (CMAKE_SYSTEM_PROCESSOR aarch64)

set (SDK_DIR "/opt/mydev/toolchain-mx93")
set (CROSS_COMPILER_PREFIX "${SDK_DIR}/sysroots/x86_64-fslbsp-linux/usr/bin/aarch64-fsl-linux/aarch64-fsl-linux-")
set (CMAKE_SYSROOT "${SDK_DIR}/sysroots/armv8a-fsl-linux/" CACHE STRING "")

set (CMAKE_C_COMPILER "${CROSS_COMPILER_PREFIX}gcc" CACHE FILEPATH "")
set (CMAKE_C_FLAGS "\
 -O1 \
 -DDEBUG \
 -w \
 -fno-strict-aliasing \
 -pipe -g -feliminate-unused-debug-types \
 -fno-omit-frame-pointer \
 -D_FORTIFY_SOURCE=2 \
 --sysroot=${CMAKE_SYSROOT} \
 " CACHE STRING "")

set (CMAKE_CXX_COMPILER "${CROSS_COMPILER_PREFIX}g++" CACHE FILEPATH "")
if (false) #these are set in my_append_compile_flags()
    set (CMAKE_CXX_FLAGS "\
     -O3 \
     -DNDEBUG \
     -Wall \
     -Wextra \
     -Wno-unused-parameter \
     -Wno-unused-result \
     -Wno-unused-variable \
     -Wno-unused-function \
     -Wno-missing-field-initializers \
     -Wno-delete-incomplete \
     -Wno-stringop-overflow \
     -Wno-array-bounds \
     -fno-strict-aliasing \
     -pipe -g -feliminate-unused-debug-types \
     -fno-omit-frame-pointer \
     -D_FORTIFY_SOURCE=2 \
     --sysroot=${CMAKE_SYSROOT} \
     " CACHE STRING "")
    # -mcpu=cortex-a53+crc+crypto \
endif()

SET(CMAKE_AR ${CROSS_COMPILER_PREFIX}ar)
SET(CMAKE_NM ${CROSS_COMPILER_PREFIX}nm)
SET(CMAKE_OBJCOPY ${CROSS_COMPILER_PREFIX}objcopy)
SET(CMAKE_OBJDUMP ${CROSS_COMPILER_PREFIX}objdump)
SET(CMAKE_RANLIB ${CROSS_COMPILER_PREFIX}ranlib)
SET(CMAKE_LINKER ${CROSS_COMPILER_PREFIX}ld)
SET(CMAKE_STRIP ${CROSS_COMPILER_PREFIX}strip)

set (CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

include_directories (SYSTEM 
    "${CMAKE_SYSROOT}/usr/include/"
    )
link_directories(
    "${SDK_DIR}/sysroots/armv8a-fsl-linux/"
    "${SDK_DIR}/sysroots/armv8a-fsl-linux/usr/lib"
    "${SDK_DIR}/sysroots/armv8a-fsl-linux/usr/lib/aarch64-fsl-linux/12.2.0"
    )

