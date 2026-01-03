# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Jucator_Radio_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Jucator_Radio_autogen.dir\\ParseCache.txt"
  "Jucator_Radio_autogen"
  )
endif()
