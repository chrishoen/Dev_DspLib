#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_init_global_import_variables)

   if(MSVC)
      set (MyRisLibIncludePath "C:/MyTools/MyLib/include/RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "C:/MyTools/MyLib/lib/RisLib.lib" PARENT_SCOPE)
      set (MyEigenIncludePath  "C:\\MyTools\\Eigen" PARENT_SCOPE)
   elseif(NOT CMAKE_SYSTEM_VERSION EQUAL 101)
      set (MyRisLibIncludePath "/usr/local/include/RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "/usr/local/lib/libRisLib.a" PARENT_SCOPE)
      set (MyEigenIncludePath "/usr/include/eigen3" PARENT_SCOPE)
   else()
      set (MyRisLibIncludePath "C:/MyTools/MyLib/include/RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "C:/MyTools/MyLib/lib/libRisLib.a" PARENT_SCOPE)
      set (MyEigenIncludePath  "C:\\MyTools\\Eigen" PARENT_SCOPE)
   endif()
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_RisLib _target)

   add_library(RisLib STATIC IMPORTED)

   set_target_properties(RisLib PROPERTIES IMPORTED_LOCATION ${MyRisLibImportPath})

   if (MSVC)
      target_link_libraries(RisLib INTERFACE ws2_32)
      target_link_libraries(RisLib INTERFACE winmm)
   else()
      if (CMAKE_SYSTEM_VERSION EQUAL 101)
         set (MyPThreadImportPath  "C:/Beagle/toolchain/arm-linux-gnueabihf/lib/libpthread.so")
      else()
         set (MyPThreadImportPath  "/usr/lib/arm-linux-gnueabihf/libpthread.so")
      endif()
      add_library(PThreadLib SHARED IMPORTED)
      set_target_properties(PThreadLib PROPERTIES IMPORTED_LOCATION ${MyPThreadImportPath})
      target_link_libraries(RisLib INTERFACE PThreadLib)
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

