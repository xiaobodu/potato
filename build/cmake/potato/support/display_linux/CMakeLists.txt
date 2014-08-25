cmake_minimum_required(VERSION 2.8)

project(display_linux)

set(SRC_PATH_display_linux ${SRC_PATH_support}/display_linux)

set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_display_linux}
  )

set(SRC_FILE_LIST
  ${SRC_PATH_display_linux}/display_linux.h
  ${SRC_PATH_display_linux}/display_linux.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(display_linux SHARED ${SRC_FILE_LIST})

set(LINK_FILE_LIST
  base
  display
  X11
  GL
  )
target_link_libraries(display_linux ${LINK_FILE_LIST})

# build dependicies
set(DEP_PROJ_LIST
  base
  display
  )
add_dependencies(display_linux ${DEP_PROJ_LIST})
