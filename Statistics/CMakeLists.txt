cmake_minimum_required (VERSION 3.8)

project (Statistics CXX)

my_find_src_files (src_files Statistics)
add_executable (Statistics ${src_files})
my_add_compile_options (Statistics)
my_add_pch (Statistics)

target_include_directories(Statistics PRIVATE DspLib)

target_link_libraries(Statistics DspLib)
