cmake_minimum_required(VERSION 2.8)

project(potato)

set(CODE_PATH_potato ${CODE_PATH}/potato)

set(INC_PATH_potato "${CODE_PATH_potato}/inc")
set(SRC_PATH_potato "${CODE_PATH_potato}/src")

# add sub-project

set(INC_PATH_LIST
  ${INC_PATH_potato}
  ${SRC_PATH_potato}
  )

include_directories(${INC_PATH_LIST})

set(SRC_FILE_LIST
  ${INC_PATH_potato}/potato.h
  ${SRC_PATH_potato}/potato.cpp
  ${SRC_PATH_potato}/common.h
  ${SRC_PATH_potato}/utility/sharedlibrary.h
  ${SRC_PATH_potato}/utility/sharedlibrary.cpp
  ${SRC_PATH_potato}/utility/file.h
  )

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

add_library(potato STATIC ${SRC_FILE_LIST})

add_subdirectory(engine)

add_subdirectory(support)
