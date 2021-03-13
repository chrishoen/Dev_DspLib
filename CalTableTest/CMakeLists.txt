cmake_minimum_required (VERSION 3.8)

project (CalTableTest CXX)

my_find_src_files (src_files CalTableTest)
add_executable (CalTableTest ${src_files})
my_add_compile_options (CalTableTest)
my_add_pch (CalTableTest)


my_inc_import_RisLib(CalTableTest)
my_lib_import_RisLib(CalTableTest)


if(MSVC)
   install(TARGETS CalTableTest DESTINATION "C:/aaa_prime/CalTable")
elseif(NOT CMAKE_SYSTEM_VERSION EQUAL 101)
   install(TARGETS CalTableTest DESTINATION "/opt/prime/bin")
else()
   add_custom_command(
      TARGET  CalTableTest
      POST_BUILD
      COMMAND rsync -azv --chmod=ugo=rwx CalTableTest rsync://debian@devtgt/prime/bin
      WORKING_DIRECTORY C:/Users/$ENV{username}/CMakeBuilds/Dev_RisLib/CalTableTest)
endif()
