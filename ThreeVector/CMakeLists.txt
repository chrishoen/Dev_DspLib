cmake_minimum_required (VERSION 3.8)

project (ThreeVector CXX)

my_find_src_files (src_files ThreeVector)
add_executable (ThreeVector ${src_files})
my_add_compile_options (ThreeVector)
my_add_pch (ThreeVector)

target_include_directories(ThreeVector PRIVATE DspLib)

target_link_libraries(ThreeVector DspLib)
