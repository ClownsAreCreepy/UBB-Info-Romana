# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TicTacToe_Joc__autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TicTacToe_Joc__autogen.dir\\ParseCache.txt"
  "TicTacToe_Joc__autogen"
  )
endif()
