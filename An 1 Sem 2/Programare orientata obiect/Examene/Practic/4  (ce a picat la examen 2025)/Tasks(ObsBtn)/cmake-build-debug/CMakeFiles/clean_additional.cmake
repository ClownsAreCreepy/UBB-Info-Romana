# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Tasks_ObsBtn__autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Tasks_ObsBtn__autogen.dir\\ParseCache.txt"
  "Tasks_ObsBtn__autogen"
  )
endif()
