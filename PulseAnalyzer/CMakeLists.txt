cmake_minimum_required (VERSION 3.8)

project (PulseAnalyzer CXX)

my_find_src_files (src_files PulseAnalyzer)
add_executable (PulseAnalyzer ${src_files})
my_add_compile_options (PulseAnalyzer)
my_add_pch (PulseAnalyzer)

target_include_directories(PulseAnalyzer PRIVATE DspLib)

target_link_libraries(PulseAnalyzer DspLib)
