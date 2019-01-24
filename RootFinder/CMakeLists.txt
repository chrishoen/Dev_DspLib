cmake_minimum_required (VERSION 3.8)

project (RootFinder CXX)

my_find_src_files (src_files RootFinder)
add_executable (RootFinder ${src_files})
my_add_compile_options (RootFinder)
my_add_pch (RootFinder)

target_include_directories(RootFinder PRIVATE DspLib)
target_include_directories(RootFinder PRIVATE ${MyEigenIncludePath})

target_link_libraries(RootFinder DspLib)
