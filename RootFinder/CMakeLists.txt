cmake_minimum_required (VERSION 3.27)

project (RootFinder CXX)
my_find_src_files (src_files RootFinder)
add_executable (RootFinder ${src_files})
my_add_compile_options (RootFinder)
my_add_pch (RootFinder)

my_inc_import_DspLib(RootFinder)
my_inc_import_Eigen(RootFinder)
my_inc_import_RisLib(RootFinder)

my_lib_import_DspLib(RootFinder)
my_lib_import_RisLib(RootFinder)
