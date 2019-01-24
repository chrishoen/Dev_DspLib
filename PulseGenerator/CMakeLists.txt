cmake_minimum_required (VERSION 3.8)

project (PulseGenerator CXX)

my_find_src_files (src_files PulseGenerator)
add_executable (PulseGenerator ${src_files})
my_add_compile_options (PulseGenerator)
my_add_pch (PulseGenerator)

target_include_directories(PulseGenerator PRIVATE DspLib)

target_link_libraries(PulseGenerator DspLib)
