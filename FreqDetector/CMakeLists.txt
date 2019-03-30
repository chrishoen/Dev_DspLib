cmake_minimum_required (VERSION 3.8)

project (FreqDetector CXX)
my_find_src_files (src_files FreqDetector)
add_executable (FreqDetector ${src_files})
my_add_compile_options (FreqDetector)
my_add_pch (FreqDetector)

my_inc_import_DspLib(FreqDetector)
my_inc_import_RisLib(FreqDetector)

my_lib_import_DspLib(FreqDetector)
my_lib_import_RisLib(FreqDetector)
