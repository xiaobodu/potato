cmake_minimum_required(VERSION 2.8)

project(display)

set(SRC_PATH_display ${SRC_PATH_support}/display_linux_gles)

set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_potato}/engine
  ${SRC_PATH_display}
  )

set(SRC_FILE_LIST
  ${SRC_PATH_potato}/engine/input.h
  ${SRC_PATH_potato}/engine/input.cpp
  ${SRC_PATH_potato}/engine/sensor.h
  ${SRC_PATH_potato}/engine/sensor.cpp
  ${SRC_PATH_display}/display_impl.h
  ${SRC_PATH_display}/display.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH ${OUT_PATH}/bin)

include_directories(${INC_PATH_LIST})

add_library(display SHARED ${SRC_FILE_LIST})

set(LINK_FILE_LIST
  X11
  EGL
  dl
  )
target_link_libraries(display ${LINK_FILE_LIST})
