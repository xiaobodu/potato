cmake_minimum_required(VERSION 2.8)

project(asset)

set(SRC_PATH_asset ${SRC_PATH_support}/asset)

set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_potato}/engine
  ${SRC_PATH_asset}
  )

set(SRC_FILE_LIST
  ${SRC_PATH_support}/../engine/asset.h
  ${SRC_PATH_asset}/asset.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(asset SHARED ${SRC_FILE_LIST})

set(LINK_FILE_LIST
  )
target_link_libraries(asset ${LINK_FILE_LIST})
