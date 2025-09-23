cmake_minimum_required (VERSION 3.27)

project (Butterworth CXX)
my_find_src_files (src_files Butterworth)
add_executable (Butterworth ${src_files})
my_add_compile_options (Butterworth)
my_add_pch (Butterworth)

my_inc_import_DspLib(Butterworth)
my_inc_import_RisLib(Butterworth)

my_lib_import_DspLib(Butterworth)
my_lib_import_RisLib(Butterworth)
