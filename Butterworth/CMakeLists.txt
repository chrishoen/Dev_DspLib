cmake_minimum_required (VERSION 3.8)

project (Butterworth CXX)

my_find_src_files (src_files Butterworth)
add_executable (Butterworth ${src_files})
my_add_compile_options (Butterworth)
my_add_pch (Butterworth)

target_include_directories(Butterworth PRIVATE DspLib)

target_link_libraries(Butterworth DspLib)
