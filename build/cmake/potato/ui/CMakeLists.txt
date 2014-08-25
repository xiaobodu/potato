cmake_minimum_required(VERSION 2.8)

project(ui)

set(RC_PATH_ui ${SRC_PATH_potato}/ui)

set(INC_PATH_LIST
  ${SRC_PATH_ui}
  )

set(RC_FILE_LIST
  ${SRC_PATH_ui}/ui.h
  ${SRC_PATH_ui}/ui.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

# compile the thread project with position independence code
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(ui STATIC ${SRC_FILE_LIST})
