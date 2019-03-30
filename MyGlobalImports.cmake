#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_init_global_import_variables)

   if(MSVC)
      set (MyRisLibIncludePath "C:\\MyTools\\MyLib\\include\\RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "C:\\MyTools\\MyLib\\lib\\RisLib.lib" PARENT_SCOPE)
      set (MyEigenIncludePath  "C:\\MyTools\\Eigen" PARENT_SCOPE)
   else()
      set (MyRisLibIncludePath "/usr/local/include/RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "/usr/local/lib/libRisLib.so" PARENT_SCOPE)
      set (MyEigenIncludePath "/usr/include/eigen3" PARENT_SCOPE)
   endif()
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_RisLib _target)

   if (MSVC)
      add_library(RisLib STATIC IMPORTED)
   else()
      add_library(RisLib SHARED IMPORTED)
   endif()

   set_target_properties(RisLib PROPERTIES IMPORTED_LOCATION ${MyRisLibImportPath})

   if (MSVC)
      target_link_libraries(RisLib INTERFACE ws2_32)
      target_link_libraries(RisLib INTERFACE winmm)
   else()
      set(THREADS_PREFER_PTHREAD_FLAG ON)
      find_package(Threads REQUIRED)
      target_link_libraries(RisLib INTERFACE Threads::Threads)
   endif()

   target_link_libraries(${_target} RisLib)

endfunction()

function(my_inc_import_RisLib _target)

   target_include_directories(${_target} PUBLIC ${MyRisLibIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_inc_import_Eigen _target)

   target_include_directories(${_target} PUBLIC ${MyEigenIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

