cmake_minimum_required (VERSION 3.27)

project (Statistics CXX)
my_find_src_files (src_files Statistics)
add_executable (Statistics ${src_files})
my_add_compile_options (Statistics)
my_add_pch (Statistics)

my_inc_import_DspLib(Statistics)
my_inc_import_RisLib(Statistics)

my_lib_import_DspLib(Statistics)
my_lib_import_RisLib(Statistics)
