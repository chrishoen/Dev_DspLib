cmake_minimum_required (VERSION 3.8)

project (HistoryTest CXX)

my_find_src_files (src_files HistoryTest)
add_executable (HistoryTest ${src_files})
my_add_compile_options (HistoryTest)
my_add_pch (HistoryTest)

target_include_directories(HistoryTest PRIVATE DspLib)

target_link_libraries(HistoryTest DspLib)
