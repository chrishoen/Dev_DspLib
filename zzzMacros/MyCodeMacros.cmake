#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_find_src_files _a_src_files _target)

   file(GLOB _src_files RELATIVE ${PROJECT_SOURCE_DIR} *.cpp *.c)

   if(MSVC)
      list(FILTER _src_files EXCLUDE REGEX ".*_linux")
   else()
      list(FILTER _src_files EXCLUDE REGEX ".*_win")
   endif()

   set(${_a_src_files} ${_src_files} PARENT_SCOPE)

   message(STATUS "my_find_src_files************************ " ${_target})
   return()
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

   if(MSVC)
      list(FILTER _src_files EXCLUDE REGEX ".*_linux")
   else()
      list(FILTER _src_files EXCLUDE REGEX ".*_win")
   endif()

   set(${_a_inc_files} ${_inc_files} PARENT_SCOPE)

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

#*******************************************
function(my_add_compile_options_c_gcc option)
   add_compile_options($<$<COMPILE_LANG_AND_ID:C,GNU>:${option}>)
endfunction()
function(my_add_compile_options_cxx_gcc option)
   add_compile_options($<$<COMPILE_LANG_AND_ID:CXX,GNU>:${option}>)
endfunction()

#*******************************************
function(my_append_compile_flags_gcc)

    message(STATUS "my_append_compile_flags_gcc************************")
    #my_add_compile_options_c_gcc(-O3)
    #my_add_compile_options_c_gcc(-w)
    #my_add_compile_options_c_gcc(-pipe)
    #my_add_compile_options_c_gcc(-feliminate-unused-debug-types)
    #my_add_compile_options_c_gcc(-fno-omit-frame-pointer)
    #my_add_compile_options_c_gcc(-mcpu=cortex-a53+crc+crypto)
    #my_add_compile_options_c_gcc(-D_FORTIFY_SOURCE=2)
    #my_add_compile_options_c_gcc(--sysroot=${CMAKE_SYSROOT})

    my_add_compile_options_cxx_gcc(-D_GNU_SOURCE)
    my_add_compile_options_cxx_gcc(-O3)
    my_add_compile_options_cxx_gcc(-Wall)
    my_add_compile_options_cxx_gcc(-Wextra)
    my_add_compile_options_cxx_gcc(-Wno-unused-parameter)
    my_add_compile_options_cxx_gcc(-Wno-unused-result)
    my_add_compile_options_cxx_gcc(-Wno-unused-variable)
    my_add_compile_options_cxx_gcc(-Wno-unused-function)
    my_add_compile_options_cxx_gcc(-Wno-unknown-pragmas)
    my_add_compile_options_cxx_gcc(-Wno-missing-field-initializers)
    my_add_compile_options_cxx_gcc(-Wno-delete-incomplete)
    my_add_compile_options_cxx_gcc(-fno-strict-aliasing)
    my_add_compile_options_cxx_gcc(-Wno-psabi)
    my_add_compile_options_cxx_gcc(-Wno-stringop-overflow)
    my_add_compile_options_cxx_gcc(-Wno-stringop-truncation)
    my_add_compile_options_cxx_gcc(-Wno-array-bounds)
    #my_add_compile_options_cxx_gcc(-pipe)
    #my_add_compile_options_cxx_gcc(-feliminate-unused-debug-types)
    #my_add_compile_options_cxx_gcc(-fno-omit-frame-pointer)
    #my_add_compile_options_cxx_gcc(-mcpu=cortex-a53+crc+crypto)
    #my_add_compile_options_cxx_gcc(-D_FORTIFY_SOURCE=2)
    #my_add_compile_options_cxx_gcc(--sysroot=${CMAKE_SYSROOT})
endfunction()

#*******************************************
function(my_append_compile_flags_msvc_release)

    message(STATUS "my_append_compile_flags_msvc_release************************")
    add_compile_options(/WX)
    add_compile_options(/wd4996)
    add_compile_options(/wd6031)
    add_compile_options(/wd6385)
    add_compile_options(/wd6387)
    add_compile_options(/MT)
    add_compile_options(/O2)
    add_compile_options(/Ot)
    add_compile_options(/Oi)
    add_compile_options(/GS-)
    add_compile_options(/Gd)

endfunction()

#*******************************************
function(my_append_compile_flags_msvc_debug)

    message(STATUS "my_append_compile_flags_msvc_debug************************")
    add_compile_options(/WX)
    add_compile_options(/wd4996)
    add_compile_options(/wd6031)
    add_compile_options(/wd6385)
    add_compile_options(/wd6387)
    add_compile_options(/Ot)
    add_compile_options(/Oi)
    add_compile_options(/MDd)
    add_compile_options(/GS-)
    add_compile_options(/Gd)
    return()

    add_compile_options(/WX)
    add_compile_options(/wd4996)
    add_compile_options(/wd6031)
    add_compile_options(/wd6385)
    #add_compile_options(/O2)
    add_compile_options(/Ot)
    add_compile_options(/Oi)
    #add_compile_options(/MT)
    add_compile_options(/GS-)
    add_compile_options(/Gd)
    #add_compile_options(/EHsc)
    #add_compile_options(/Zc:wchar_t)
    add_compile_options(/Zc:inline)
    add_compile_options(/D_MBCS)

endfunction()

#*******************************************
function(my_append_compile_flags)
   if(MSVC)
      if (CMAKE_BUILD_TYPE MATCHES "Release")
         my_append_compile_flags_msvc_release()
      else()
         my_append_compile_flags_msvc_debug()
      endif()
   elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
      my_append_compile_flags_gcc()
   endif()
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_add_compile_options _target)
   return()
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_add_compile_options_so _target)
   return()
endfunction()

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
