#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_RisLib _target)

   if (MSVC)
      set (MyRisLibImportPath  "C:/MyTools/MyLib/lib/RisLib.lib")
   elseif (MYMODE STREQUAL "beagle")
      set (MyRisLibImportPath  "C:/MyTools/MyLib/lib/libRisLib.a")
   elseif (MYMODE STREQUAL "steno-arm")
      set (MyRisLibImportPath  "/mnt/c/Prime/AAA_Stenograph/NextGen/src_linux/gui/target/rislib/lib/arm/libRisLib.a")
   else()
      set (MyRisLibImportPath  "/opt/prime/lib/libRisLib.a")
   endif()

   if (MSVC)
      add_library(RisLib STATIC IMPORTED)
      set_target_properties(RisLib PROPERTIES IMPORTED_LOCATION ${MyRisLibImportPath})
      target_link_libraries(RisLib INTERFACE ws2_32)
      target_link_libraries(RisLib INTERFACE winmm)
      target_link_libraries(${_target} RisLib)
   elseif (MYMODE STREQUAL "beagle")
      add_library(RisLib STATIC IMPORTED)
      set_target_properties(RisLib PROPERTIES IMPORTED_LOCATION ${MyRisLibImportPath})
      target_link_libraries(${_target} RisLib)
      target_link_libraries(${_target} pthread)
      target_link_libraries(${_target} rt)
      target_link_libraries(${_target} readline)
      target_link_libraries(${_target} atomic)
   else()
      add_library(RisLib STATIC IMPORTED)
      set_target_properties(RisLib PROPERTIES IMPORTED_LOCATION ${MyRisLibImportPath})
      target_link_libraries(${_target} RisLib)
      target_link_libraries(${_target} pthread)
      target_link_libraries(${_target} rt)
      target_link_libraries(${_target} readline)
   endif()

endfunction()

function(my_inc_import_RisLib _target)

   if (MSVC OR MYMODE STREQUAL "beagle")
      set (MyRisLibIncludePath "C:/MyTools/MyLib/include/RisLib")
#  elseif(MYMODE STREQUAL "steno-arm")
#     set (MyRisLibIncludePath  "/mnt/c/Prime/AAA_Stenograph/NextGen/src_linux/gui/target/rislib/include")
   else()
      set (MyRisLibIncludePath "/opt/prime/include/RisLib")
   endif()

   target_include_directories(${_target} PUBLIC ${MyRisLibIncludePath})

endfunction()


#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_inc_import_Eigen _target)

   if(MSVC)
      set (MyEigenIncludePath  "C:/MyTools/Eigen")
   elseif(CMAKE_SYSTEM_VERSION EQUAL 101)
      set (MyEigenIncludePath  "C:/MyTools/Eigen")
   else()
      set (MyEigenIncludePath  "/usr/include/eigen3")
   endif()

   target_include_directories(${_target} PUBLIC ${MyEigenIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

