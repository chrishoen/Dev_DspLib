cmake_minimum_required (VERSION 3.8)

project (FuzzyBool CXX)
my_find_src_files (src_files FuzzyBool)
add_executable (FuzzyBool ${src_files})
my_add_compile_options (FuzzyBool)
my_add_pch (FuzzyBool)

my_inc_import_DspLib(FuzzyBool)
my_inc_import_RisLib(FuzzyBool)

my_lib_import_DspLib(FuzzyBool)
my_lib_import_RisLib(FuzzyBool)

