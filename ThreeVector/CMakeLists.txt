cmake_minimum_required (VERSION 3.27)

project (ThreeVector CXX)
my_find_src_files (src_files ThreeVector)
add_executable (ThreeVector ${src_files})
my_add_compile_options (ThreeVector)
my_add_pch (ThreeVector)

my_inc_import_DspLib(ThreeVector)
my_inc_import_RisLib(ThreeVector)

my_lib_import_DspLib(ThreeVector)
my_lib_import_RisLib(ThreeVector)
