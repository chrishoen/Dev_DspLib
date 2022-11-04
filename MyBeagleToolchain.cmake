# this one is important
SET(CMAKE_SYSTEM_NAME Linux)

# specify the cross compiler
SET(CMAKE_C_COMPILER
C:/Beagle/toolchain/bin/arm-linux-gnueabihf-gcc.exe)
SET(CMAKE_CXX_COMPILER
C:/Beagle/toolchain/bin/arm-linux-gnueabihf-g++.exe)
# where is the target environment
SET(CMAKE_FIND_ROOT_PATH
C:/Beagle/toolchain)
# for cmake 3.8
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)