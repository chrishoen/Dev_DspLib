#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_add_pch22 _target)

   if (MYMODE STREQUAL "prime-rpi-win" OR MYMODE STREQUAL "prime-writer-win")
      return()
   endif()

   target_precompile_headers(${_target} PRIVATE "stdafx.h")

endfunction()

function(my_add_pch _target)

   target_precompile_headers(${_target} PRIVATE "stdafx.h")

endfunction()
