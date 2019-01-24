cmake_minimum_required (VERSION 3.8)

project (RVectorTest CXX)

my_find_src_files (src_files RVectorTest)
add_executable (RVectorTest ${src_files})
my_add_compile_options (RVectorTest)
my_add_pch (RVectorTest)

target_include_directories(RVectorTest PRIVATE DspLib)

target_link_libraries(RVectorTest DspLib)
