cmake_minimum_required (VERSION 3.8)

project (FileTest CXX)

my_find_src_files (src_files FileTest)
add_executable (FileTest ${src_files})
my_add_compile_options (FileTest)
my_add_pch (FileTest)

target_include_directories(FileTest PRIVATE DspLib)

target_link_libraries(FileTest DspLib)
