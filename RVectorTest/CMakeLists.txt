cmake_minimum_required (VERSION 3.8)

project (RVectorTest CXX)
my_find_src_files (src_files RVectorTest)
add_executable (RVectorTest ${src_files})
my_add_compile_options (RVectorTest)
my_add_pch (RVectorTest)

my_inc_import_DspLib(RVectorTest)
my_inc_import_RisLib(RVectorTest)

my_lib_import_DspLib(RVectorTest)
my_lib_import_RisLib(RVectorTest)
