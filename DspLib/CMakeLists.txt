cmake_minimum_required (VERSION 3.8)

project (DspLib CXX)

my_find_src_files (src_files DspLib)
my_find_inc_files (inc_files)
add_library (DspLib STATIC ${src_files})
my_add_compile_options (DspLib)
my_add_pch (DspLib)

target_include_directories(DspLib PUBLIC ${PROJECT_SOURCE_DIR})

find_package(RisLib CONFIG REQUIRED PATHS ${MyRisLibConfigPath} NO_DEFAULT_PATH)
target_include_directories(DspLib PUBLIC RisLib)
target_link_libraries(DspLib RisLib)

if (MSVC)
   install(FILES ${inc_files} DESTINATION "C:\\MyTools\\MyLib\\include\\DspLib")
   install(TARGETS DspLib DESTINATION "C:\\MyTools\\MyLib\\lib")
   install(FILES DspLibConfig.cmake DESTINATION "C:\\MyTools\\MyLib\\lib\\cmake\\DspLib")
else()
   install(FILES ${inc_files} DESTINATION "/usr/local/include/DspLib")
   install(FILES "/var/tmp/Dev_DspLibLx/build/DspLib/libDspLib.a" DESTINATION "/usr/local/lib")
   #install(TARGETS DspLib DESTINATION "//usr/local/lib")
   install(FILES DspLibConfig.cmake DESTINATION "/usr/local/lib/cmake/DspLib")
endif()
