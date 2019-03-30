cmake_minimum_required (VERSION 3.8)

project (DelayTest CXX)
my_find_src_files (src_files DelayTest)
add_executable (DelayTest ${src_files})
my_add_compile_options (DelayTest)
my_add_pch (DelayTest)

my_inc_import_DspLib(DelayTest)
my_inc_import_RisLib(DelayTest)

my_lib_import_DspLib(DelayTest)
my_lib_import_RisLib(DelayTest)
