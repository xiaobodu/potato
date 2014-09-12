cmake_minimum_required(VERSION 2.8)

project(script_tcc)

set(SRC_PATH_script_tcc ${SRC_PATH_support}/script_tcc)

set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_potato}/engine
  ${CODE_PATH}/external/tinycc
  ${SRC_PATH_script_tcc}
  )

set(SRC_FILE_LIST
  ${SRC_PATH_support}/../engine/script.h
  ${SRC_PATH_script_tcc}/script_impl.h
  ${SRC_PATH_script_tcc}/script.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(script_tcc SHARED ${SRC_FILE_LIST})

set(LINK_FILE_LIST
  tinycc
  )
target_link_libraries(script_tcc ${LINK_FILE_LIST})

add_dependencies(script_tcc tinycc)
