#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_special1)

   message(STATUS "my_special1***********************************************************BEGIN")
   message(STATUS "CMAKE_SYSTEM_PROCESSOR   " ${CMAKE_SYSTEM_PROCESSOR})
   message(STATUS "CMAKE_C_COMPILER         " ${CMAKE_C_COMPILER})
   message(STATUS "CMAKE_CXX_COMPILER       " ${CMAKE_CXX_COMPILER})
   message(STATUS "CMAKE_C_FLAGS            " ${CMAKE_C_FLAGS})
   message(STATUS "CMAKE_CXX_FLAGS          " ${CMAKE_CXX_FLAGS})
   message(STATUS "CMAKE_SYSROOT            " ${CMAKE_SYSROOT})
   message(STATUS "CMAKE_TOOLCHAIN_FILE     " ${CMAKE_TOOLCHAIN_FILE})
   message(STATUS "MYMODE                 " ${MYMODE})
   message(STATUS "my_special1***********************************************************END")

   return()
   message(STATUS "MYMODE                 " ${MYMODE})
   message(STATUS "CMAKE_SYSTEM           " ${CMAKE_SYSTEM})
   message(STATUS "CMAKE_BUILD_TYPE       " ${CMAKE_BUILD_TYPE})
   message(STATUS "CMAKE_INSTALL_PREFIX   " ${CMAKE_INSTALL_PREFIX})
   message(STATUS "PROJECT_SOURCE_DIR     " ${PROJECT_SOURCE_DIR})
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

