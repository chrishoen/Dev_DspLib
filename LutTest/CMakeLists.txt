cmake_minimum_required (VERSION 3.8)

project (LutTest CXX)
my_find_src_files (src_files LutTest)
add_executable (LutTest ${src_files})
my_add_compile_options (LutTest)
my_add_pch (LutTest)

my_inc_import_DspLib(LutTest)
my_inc_import_RisLib(LutTest)

my_lib_import_DspLib(LutTest)
my_lib_import_RisLib(LutTest)
