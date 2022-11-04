SET (CMAKE_CXX_STANDARD 17)
SET (CMAKE_CXX_STANDARD_REQUIRED on)

#message(FATAL_ERROR "############# CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR} #############")

set (CMAKE_SYSTEM_NAME Linux)
set (CMAKE_SYSTEM_PROCESSOR aarch64)

set (SDK_DIR $ENV{SDK_DIR})
set (CROSS_COMPILER_PREFIX "${SDK_DIR}/sysroots/x86_64-fslcsdk-linux/usr/bin/aarch64-fslc-linux/aarch64-fslc-linux-")
set (CMAKE_SYSROOT "${SDK_DIR}/sysroots/aarch64-fslc-linux/" CACHE STRING "")

set (CMAKE_C_COMPILER "${CROSS_COMPILER_PREFIX}gcc" CACHE FILEPATH "")
set (CMAKE_C_FLAGS 
"-O1 -DDEBUG -w -fno-strict-aliasing -pipe -g -feliminate-unused-debug-types -frecord-gcc-switches -fno-omit-frame-pointer -mcpu=cortex-a53+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 --sysroot=${CMAKE_SYSROOT}"
 CACHE STRING "")

set (CMAKE_CXX_COMPILER "${CROSS_COMPILER_PREFIX}g++" CACHE FILEPATH "")
set (CMAKE_CXX_FLAGS 
"-O3 -DNDEBUG -Wall -Wextra -Wno-unused-parameter -Wno-unused-result -Wno-unused-variable -Wno-unused-function -fno-strict-aliasing -pipe -g -feliminate-unused-debug-types -frecord-gcc-switches -fno-omit-frame-pointer -mcpu=cortex-a53+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 --sysroot=${CMAKE_SYSROOT}"
 CACHE STRING "")


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
    "${SDK_DIR}/sysroots/aarch64-fslc-linux/"
    "${SDK_DIR}/sysroots/aarch64-fslc-linux/usr/lib"
    "${SDK_DIR}/sysroots/aarch64-fslc-linux/usr/lib/aarch64-fslc-linux/9.3.0"
    )

return()
set (CMAKE_C_FLAGS 
"-O1 -DDEBUG -Wall -Wextra -fno-strict-aliasing -pipe -g -feliminate-unused-debug-types -frecord-gcc-switches -fno-omit-frame-pointer -mcpu=cortex-a53+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 --sysroot=${CMAKE_SYSROOT}"
 CACHE STRING "")
