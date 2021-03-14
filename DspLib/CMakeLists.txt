cmake_minimum_required (VERSION 3.8)

project (DspLib CXX)

my_find_src_files (src_files DspLib)
my_find_inc_files (inc_files)

if (MSVC)
   add_library (DspLib STATIC ${src_files})
else()
   add_library (DspLib SHARED ${src_files})
endif()
my_add_compile_options (DspLib)
my_add_pch (DspLib)

target_include_directories(DspLib PUBLIC ${PROJECT_SOURCE_DIR})

my_inc_import_RisLib(DspLib)

if (MSVC)
   my_lib_import_RisLib(DspLib)
endif()

if (MSVC)
   install(FILES ${inc_files} DESTINATION "C:/MyTools/MyLib/include/DspLib")
   install(TARGETS DspLib DESTINATION "C:/MyTools/MyLib/lib")
elseif(NOT CMAKE_SYSTEM_VERSION EQUAL 101)
   install(FILES ${inc_files} DESTINATION "/opt/prime/include/DspLib")
   install(TARGETS DspLib DESTINATION "/opt/prime/lib")
else()
   install(FILES ${inc_files} DESTINATION "C:/MyTools/MyLib/include/DspLib")
   install(TARGETS DspLib DESTINATION "C:/MyTools/MyLib/lib")
   add_custom_command(
      TARGET  DspLib
      POST_BUILD
      COMMAND rsync -azv --chmod=ugo=rwx libDspLib.so rsync://debian@devtgt/prime/lib
      WORKING_DIRECTORY C:/Users/$ENV{username}/CMakeBuilds/Dev_DspLib/DspLib)
endif()
