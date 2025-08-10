cmake_minimum_required(VERSION 3.10)
set (project "PulseTest")
project(${project} CXX)
my_find_src_files (src_files ${project})
add_executable (${project} ${src_files})
my_add_compile_options (${project})
my_add_pch (${project})

my_inc_import_DspLib(${project})
my_inc_import_RisLib(${project})

my_lib_import_DspLib(${project})
my_lib_import_RisLib(${project})

include("${MY_MACRO_DIR}/MyInstall.cmake")
