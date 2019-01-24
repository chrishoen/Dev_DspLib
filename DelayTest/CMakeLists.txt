cmake_minimum_required (VERSION 3.8)

project (DelayTest CXX)

my_find_src_files (src_files DelayTest)
add_executable (DelayTest ${src_files})
my_add_compile_options (DelayTest)
my_add_pch (DelayTest)

target_include_directories(DelayTest PRIVATE DspLib)

target_link_libraries(DelayTest DspLib)
