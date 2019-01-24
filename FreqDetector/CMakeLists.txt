cmake_minimum_required (VERSION 3.8)

project (FreqDetector CXX)

my_find_src_files (src_files FreqDetector)
add_executable (FreqDetector ${src_files})
my_add_compile_options (FreqDetector)
my_add_pch (FreqDetector)

target_include_directories(FreqDetector PRIVATE DspLib)

target_link_libraries(FreqDetector DspLib)
