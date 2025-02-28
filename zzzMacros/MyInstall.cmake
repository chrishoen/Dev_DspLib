cmake_minimum_required(VERSION 3.10)

if (MSVC)
   install(TARGETS ${project} DESTINATION "C:/aaa_prime/bin")
elseif (MYMODE STREQUAL "prime-beagle-win")
   install(CODE "execute_process(COMMAND_ECHO STDOUT
      COMMAND c:/windows/system32/openssh/scp ${CMAKE_CURRENT_BINARY_DIR}/${project} debian@bbx:/opt/prime/bin)")
elseif (MYMODE STREQUAL "prime-rpi-win")
   install(CODE "execute_process(COMMAND_ECHO STDOUT
      COMMAND c:/windows/system32/openssh/scp ${CMAKE_CURRENT_BINARY_DIR}/${project} rpx1:/opt/prime/bin)")
elseif (MYMODE STREQUAL "prime-writer-win")
   install(CODE "execute_process(COMMAND_ECHO STDOUT
      COMMAND c:/windows/system32/openssh/scp ${CMAKE_CURRENT_BINARY_DIR}/${project} writer:/opt/prime/bin)")
elseif(MYMODE STREQUAL "prime-ubu")
   install(TARGETS ${project} DESTINATION "/opt/prime/bin")
#  install(CODE "execute_process(COMMAND_ECHO STDOUT
#     COMMAND scp ${CMAKE_CURRENT_BINARY_DIR}/${project} cpdev1:/opt/prime/bin)")
elseif (MYMODE STREQUAL "prime-rpi-ubu")
   install(CODE "execute_process(COMMAND_ECHO STDOUT
      COMMAND scp ${CMAKE_CURRENT_BINARY_DIR}/${project} rpx1:/opt/prime/bin)")
#   install(CODE "execute_process(COMMAND_ECHO STDOUT
#      COMMAND scp ${CMAKE_CURRENT_BINARY_DIR}/${project} rpx4:/opt/prime/bin)")
elseif (MYMODE STREQUAL "prime-writer-ubu")
   install(CODE "execute_process(COMMAND_ECHO STDOUT
      COMMAND scp ${CMAKE_CURRENT_BINARY_DIR}/${project} writer:/opt/prime/bin)")
endif()

