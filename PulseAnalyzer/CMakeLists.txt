cmake_minimum_required (VERSION 3.8)

project (PulseAnalyzer CXX)
my_find_src_files (src_files PulseAnalyzer)
add_executable (PulseAnalyzer ${src_files})
my_add_compile_options (PulseAnalyzer)
my_add_pch (PulseAnalyzer)

my_inc_import_DspLib(PulseAnalyzer)
my_inc_import_RisLib(PulseAnalyzer)

my_lib_import_DspLib(PulseAnalyzer)
my_lib_import_RisLib(PulseAnalyzer)
