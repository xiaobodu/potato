cmake_minimum_required(VERSION 2.8)

project(display_linux_gl)

set(SRC_PATH_display_linux_gl ${SRC_PATH_support}/display_linux_gl)

set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_potato}/engine
  ${SRC_PATH_display_linux_gl}
  )

set(SRC_FILE_LIST
  ${SRC_PATH_display_linux_gl}/display_linux_gl.h
  ${SRC_PATH_display_linux_gl}/display_linux_gl.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(display_linux_gl SHARED ${SRC_FILE_LIST})

set(LINK_FILE_LIST
  X11
  GL
  dl
  )
target_link_libraries(display_linux_gl ${LINK_FILE_LIST})
