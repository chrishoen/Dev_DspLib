cmake_minimum_required (VERSION 3.8)

project (LLogic CXX)
my_find_src_files (src_files LLogic)
add_executable (LLogic ${src_files})
my_add_compile_options (LLogic)
my_add_pch (LLogic)

my_inc_import_DspLib(LLogic)
my_inc_import_RisLib(LLogic)

my_lib_import_DspLib(LLogic)
my_lib_import_RisLib(LLogic)

