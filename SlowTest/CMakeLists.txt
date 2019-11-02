cmake_minimum_required (VERSION 3.8)

project (SlowTest CXX)
my_find_src_files (src_files SlowTest)
add_executable (SlowTest ${src_files})
my_add_compile_options (SlowTest)
my_add_pch (SlowTest)

my_inc_import_RisLib(SlowTest)
my_inc_import_DspLib(SlowTest)

my_lib_import_RisLib(SlowTest)
my_lib_import_DspLib(SlowTest)

