# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Produse_Observer__autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Produse_Observer__autogen.dir\\ParseCache.txt"
  "Produse_Observer__autogen"
  )
endif()
