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
   install(FILES ${inc_files} DESTINATION "C:\\MyTools\\MyLib\\include\\DspLib")
   install(TARGETS DspLib DESTINATION "C:\\MyTools\\MyLib\\lib")
else()
   install(FILES ${inc_files} DESTINATION "/usr/local/include/DspLib")
   install(TARGETS DspLib DESTINATION "/usr/local/lib")
endif()
