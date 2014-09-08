cmake_minimum_required(VERSION 2.8)

project(scene)

set(SRC_PATH_scene ${SRC_PATH_support}/scene)

set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_potato}/engine
  ${SRC_PATH_scene}
  )

set(SRC_FILE_LIST
  ${SRC_PATH_support}/../engine/scene.h
  ${SRC_PATH_scene}/scene.cpp
  ${SRC_PATH_potato}/utility/file.h
  ${SRC_PATH_potato}/utility/log.h
  ${SRC_PATH_potato}/utility/sharedlibrary.h
  ${SRC_PATH_potato}/utility/sharedlibrary.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(scene SHARED ${SRC_FILE_LIST})

set(LINK_FILE_LIST
  dl
  )
target_link_libraries(scene ${LINK_FILE_LIST})
