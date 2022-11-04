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

   if(MSVC)
      target_compile_options(${_target} PRIVATE "/WX")
      target_compile_options(${_target} PRIVATE "/wd4996")
      target_compile_options(${_target} PRIVATE "/wd6031")
      target_compile_options(${_target} PRIVATE "/wd6385")

      target_compile_options(${_target} PRIVATE "/O2")
      target_compile_options(${_target} PRIVATE "/Ot")
      target_compile_options(${_target} PRIVATE "/Oi")

      target_compile_options(${_target} PRIVATE "/MT")
      target_compile_options(${_target} PRIVATE "/GS-")
      target_compile_options(${_target} PRIVATE "/Gd")

      target_compile_options(${_target} PRIVATE "/EHsc")
      target_compile_options(${_target} PRIVATE "/MT")
      target_compile_options(${_target} PRIVATE "/Zc:wchar_t")
      target_compile_options(${_target} PRIVATE "/Zc:inline")

      target_compile_options(${_target} PRIVATE "/D_MBCS")
   else()
      target_compile_options(${_target} PRIVATE "-std=c++17")
      target_compile_options(${_target} PRIVATE "-fexceptions")
      target_compile_options(${_target} PRIVATE "-O3")
      target_compile_options(${_target} PRIVATE "-fthreadsafe-statics")
      target_compile_options(${_target} PRIVATE "-frtti")
#     target_compile_options(${_target} PRIVATE "-fomit-frame-pointer")

#     target_compile_options(${_target} PRIVATE "-w")
#     target_compile_options(${_target} PRIVATE "-Werror")
#     target_compile_options(${_target} PRIVATE "-Wfatal-errors")
      target_compile_options(${_target} PRIVATE "-Wno-unused-result")
      target_compile_options(${_target} PRIVATE "-Wno-stringop-overflow")
      target_compile_options(${_target} PRIVATE "-Wno-deprecated-declarations")
      target_compile_options(${_target} PRIVATE "-Wno-delete-incomplete")
      target_compile_options(${_target} PRIVATE "-Wno-format")
      target_compile_options(${_target} PRIVATE "-Wno-write-strings")
      target_compile_options(${_target} PRIVATE "-Wno-psabi")
      target_compile_options(${_target} PRIVATE "-Wno-unused-local-typedefs")
      target_compile_options(${_target} PRIVATE "-Wno-cast-function-type")
      target_compile_options(${_target} PRIVATE "-Wno-reorder")
#     target_compile_options(${_target} PRIVATE "-Wno-pragma-once-outside-header")

      target_compile_definitions(${_target} PRIVATE "-DNDEBUG")
   endif()

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_add_compile_options_so _target)
   message(STATUS "my_add_compile_options************************ " ${_target})
   #message(STATUS "CMAKE_CXX_FLAGS************************ " ${CMAKE_CXX_FLAGS})
   #message(STATUS "CMAKE_CXX_FLAGS_RELEASE**************** " ${CMAKE_CXX_FLAGS_RELEASE})

   if(MSVC)
      target_compile_options(${_target} PRIVATE "/WX")
      target_compile_options(${_target} PRIVATE "/wd4996")
      target_compile_options(${_target} PRIVATE "/wd6031")
      target_compile_options(${_target} PRIVATE "/wd6385")

      target_compile_options(${_target} PRIVATE "/O2")
      target_compile_options(${_target} PRIVATE "/Ot")
      target_compile_options(${_target} PRIVATE "/Oi")

      target_compile_options(${_target} PRIVATE "/MT")
      target_compile_options(${_target} PRIVATE "/GS-")
      target_compile_options(${_target} PRIVATE "/Gd")

      target_compile_options(${_target} PRIVATE "/EHsc")
      target_compile_options(${_target} PRIVATE "/MT")
      target_compile_options(${_target} PRIVATE "/Zc:wchar_t")
      target_compile_options(${_target} PRIVATE "/Zc:inline")

      target_compile_options(${_target} PRIVATE "/D_MBCS")
   else()
      target_compile_options(${_target} PRIVATE "-std=c++11")
      target_compile_options(${_target} PRIVATE "-fexceptions")
      target_compile_options(${_target} PRIVATE "-O3")
      target_compile_options(${_target} PRIVATE "-fthreadsafe-statics")
      target_compile_options(${_target} PRIVATE "-frtti")
#     target_compile_options(${_target} PRIVATE "-fomit-frame-pointer")
      target_compile_options(${_target} PRIVATE "-fPIC")

#     target_compile_options(${_target} PRIVATE "-w")
#     target_compile_options(${_target} PRIVATE "-Werror")
#     target_compile_options(${_target} PRIVATE "-Wfatal-errors")
      target_compile_options(${_target} PRIVATE "-Wno-stringop-overflow")
      target_compile_options(${_target} PRIVATE "-Wno-deprecated-declarations")
      target_compile_options(${_target} PRIVATE "-Wno-delete-incomplete")
      target_compile_options(${_target} PRIVATE "-Wno-format")
      target_compile_options(${_target} PRIVATE "-Wno-write-strings")
      target_compile_options(${_target} PRIVATE "-Wno-psabi")
#     target_compile_options(${_target} PRIVATE "-Wno-pragma-once-outside-header")

      target_compile_definitions(${_target} PRIVATE "-DNDEBUG")
   endif()

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
