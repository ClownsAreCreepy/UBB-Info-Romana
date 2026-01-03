# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Tractoare_ClickDesen__autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Tractoare_ClickDesen__autogen.dir\\ParseCache.txt"
  "Tractoare_ClickDesen__autogen"
  )
endif()
