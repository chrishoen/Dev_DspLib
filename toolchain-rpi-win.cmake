set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER "C:/MyDev/toolchain-rpi/bin/aarch64-none-linux-gnu-gcc.exe")
set(CMAKE_CXX_COMPILER "C:/MyDev/toolchain-rpi/bin/aarch64-none-linux-gnu-g++.exe")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

include_directories (SYSTEM 
    "C:/MyDev/toolchain-rpi/aarch64-none-linux-gnu/sysroot/usr/include/"
    "C:/MyDev/toolchain-rpi/aarch64-none-linux-gnu/sysroot/usr/include/aarch64-linux-gnu"
    )

link_directories(
    "C:/MyDev/toolchain-rpi/aarch64-none-linux-gnu/libc/usr/lib64"
    "C:/MyDev/toolchain-rpi/aarch64-none-linux-gnu/sysroot/lib/aarch64-linux-gnu"
    "C:/MyDev/toolchain-rpi/aarch64-none-linux-gnu/sysroot/usr/lib/aarch64-linux-gnu"
    )

