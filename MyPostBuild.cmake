#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_init_post_build_variables)

   if(MSVC)
   elseif(CMAKE_SYSTEM_VERSION EQUAL 101)
      set (MyRsyncBin "rsync://pi@devtgt:/prime/bin" PARENT_SCOPE)
      set (MyRsyncLib "rsync://pi@devtgt:/prime/lib" PARENT_SCOPE)
   else()
      set (MyRsyncBin "rsync://main@devtgt:/prime/bin" PARENT_SCOPE)
      set (MyRsyncLib "rsync://main@devtgt:/prime/lib" PARENT_SCOPE)
   endif()

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_post_build_lib _target)

   add_custom_command(
      TARGET  ${_target}
      POST_BUILD
      COMMAND rsync -azv --chmod=ugo=rwx lib${_target}.so ${MyRsyncLib})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_post_build_bin _target)

   add_custom_command(
      TARGET  ${_target}
      POST_BUILD
      COMMAND rsync -azv --chmod=ugo=rwx ${_target} ${MyRsyncBin})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************
