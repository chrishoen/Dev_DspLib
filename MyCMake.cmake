#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_find_src_files _a_src_files _target)

   file(GLOB _src_files RELATIVE ${PROJECT_SOURCE_DIR} *.cpp)

   if(MSVC)
      list(FILTER _src_files EXCLUDE REGEX ".*_linux.cpp$")
   else()
      list(FILTER _src_files EXCLUDE REGEX ".*_win.cpp$")
   endif()

   set(${_a_src_files} ${_src_files} PARENT_SCOPE)


   message(STATUS "***********************************************************" ${_target})
   message(STATUS "my_find_src_files************************BEGIN " ${_target})
   foreach(_src_file ${_src_files})
      message(STATUS ${_src_file})
   endforeach()
   message(STATUS "my_find_src_files************************END")
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_find_inc_files _a_inc_files)

   file(GLOB _inc_files ${PROJECT_SOURCE_DIR}/*.h)
   set(${_a_inc_files} ${_inc_files} PARENT_SCOPE)

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_add_compile_options _target)
   message(STATUS "my_add_compile_options************************ " ${_target})
   
   if(MSVC)
      target_compile_options(${_target} PRIVATE "/WX")
      target_compile_options(${_target} PRIVATE "/wd4996")

      target_compile_options(${_target} PRIVATE "/O2")
      target_compile_options(${_target} PRIVATE "/Ot")
      target_compile_options(${_target} PRIVATE "/Oi")

      target_compile_options(${_target} PRIVATE "/GS-")
      target_compile_options(${_target} PRIVATE "/Gd")

      target_compile_options(${_target} PRIVATE "/EHsc")
      target_compile_options(${_target} PRIVATE "/MD")
      target_compile_options(${_target} PRIVATE "/Zc:wchar_t")
      target_compile_options(${_target} PRIVATE "/Zc:inline")

      target_compile_options(${_target} PRIVATE "/D_MBCS")
   else()
      target_compile_options(${_target} PRIVATE "-std=c++11")
      target_compile_options(${_target} PRIVATE "-fexceptions")
      target_compile_options(${_target} PRIVATE "-O3")
      target_compile_options(${_target} PRIVATE "-fthreadsafe-statics")
      target_compile_options(${_target} PRIVATE "-frtti")
      target_compile_options(${_target} PRIVATE "-fomit-frame-pointer")

      target_compile_options(${_target} PRIVATE "-w")
      target_compile_options(${_target} PRIVATE "-Wswitch")
      target_compile_options(${_target} PRIVATE "-Wno-deprecated-declarations")
      target_compile_options(${_target} PRIVATE "-Wempty-body")
      target_compile_options(${_target} PRIVATE "-Wconversion")
      target_compile_options(${_target} PRIVATE "-Wreturn-type")
      target_compile_options(${_target} PRIVATE "-Wparentheses")
      target_compile_options(${_target} PRIVATE "-Wno-format")
      target_compile_options(${_target} PRIVATE "-Wuninitialized")
      target_compile_options(${_target} PRIVATE "-Wunreachable-code")
      target_compile_options(${_target} PRIVATE "-Wunused-function")
      target_compile_options(${_target} PRIVATE "-Wunused-value")
      target_compile_options(${_target} PRIVATE "-Wunused-variable")

      target_compile_definitions(${_target} PRIVATE "-DNDEBUG")
   endif()

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_add_pch _target)
   if (NOT MSVC)
      return()
   endif()

   message(STATUS "my_add_pch************************************ " ${_target})

   get_target_property(_src_files      ${_target} SOURCES)
   get_target_property(_tgt_binary_dir ${_target} BINARY_DIR)
   get_target_property(_tgt_name       ${_target} NAME)

   #message(STATUS "my_add_pch PROJECT_SOURCE_DIR***********" ${PROJECT_SOURCE_DIR})
   #message(STATUS "my_add_pch PROJECT_BINARY_DIR***********" ${PROJECT_BINARY_DIR})
   #message(STATUS "my_add_pch _src_files*******************" ${_src_files})
   #message(STATUS "my_add_pch _tgt_binary_dir**************" ${_tgt_binary_dir})
   #message(STATUS "my_add_pch _tgt_name********************" ${_tgt_name})

   foreach(_src_file ${_src_files})
      if(${_src_file} MATCHES "stdafx.cpp") 
         #message(STATUS "_src_fileEQ*******************" ${_src_file})
         set_source_files_properties(${_src_file} PROPERTIES
         COMPILE_FLAGS "/Yc\"stdafx.h\" /Fp\"${_tgt_binary_dir}\\${_tgt_name}.pch\""
         OBJECT_OUTPUTS "${_tgt_binary_dir}\\${_tgt_name}.pch")
      else()
         #message(STATUS "_src_fileNE*******************" ${_src_file})
         set_source_files_properties(${_src_file} PROPERTIES
         COMPILE_FLAGS "/Yu\"stdafx.h\" /Fp\"${_tgt_binary_dir}\\${_tgt_name}.pch\""
         OBJECT_DEPENDS "${_tgt_binary_dir}\\${_tgt_name}.pch")
      endif()
   endforeach()
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************
#*******************************************************************************
#*******************************************************************************
#*******************************************************************************


#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_show_src_files a_src_files _target)
   message(STATUS "my_show_src_files*****************BEGIN " ${_target})
   foreach(_src_file ${${a_src_files}})
      message(STATUS ${_src_file})
   endforeach()
   message(STATUS "my_show_src_files*****************END")
endfunction()
