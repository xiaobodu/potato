cmake_minimum_required(VERSION 2.8)

project(engine)

set(SRC_PATH_engine ${SRC_PATH_potato}/engine)

set(INC_PATH_LIST
  ${INC_PATH_potato}
  ${SRC_PATH_engine}
  ${SRC_PATH_potato}/base
  ${SRC_PATH_potato}/thread
  ${SRC_PATH_potato}/utility
  )

set(SRC_FILE_LIST
  ${SRC_PATH_engine}/engine.h
  ${SRC_PATH_engine}/engine.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(engine SHARED ${SRC_FILE_LIST})

set(LINK_FILE_LIST
  base
  thread
  potato
  pthread
  )
target_link_libraries(engine ${LINK_FILE_LIST})

# build dependicies
set(DEP_PROJ_LIST
  base
  thread
  potato
  )
add_dependencies(engine ${DEP_PROJ_LIST})
