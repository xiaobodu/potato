cmake_minimum_required(VERSION 2.8)

project(thread)

set(SRC_PATH_thread ${SRC_PATH_potato}/thread)

set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_thread}
  )

set(SRC_FILE_LIST
  ${SRC_PATH_thread}/thread.h
  ${SRC_PATH_thread}/thread.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

# compile the thread project with position independance code
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(thread STATIC ${SRC_FILE_LIST})
