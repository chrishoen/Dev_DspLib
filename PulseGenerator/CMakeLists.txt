cmake_minimum_required (VERSION 3.8)

project (PulseGenerator CXX)
my_find_src_files (src_files PulseGenerator)
add_executable (PulseGenerator ${src_files})
my_add_compile_options (PulseGenerator)
my_add_pch (PulseGenerator)

my_inc_import_DspLib(PulseGenerator)
my_inc_import_RisLib(PulseGenerator)

my_lib_import_DspLib(PulseGenerator)
my_lib_import_RisLib(PulseGenerator)
