cmake_minimum_required(VERSION 2.8)

project(render)

set(RC_PATH_render ${SRC_PATH_potato}/render)

set(INC_PATH_LIST
  ${SRC_PATH_render}
  )

set(RC_FILE_LIST
  ${SRC_PATH_render}/render.h
  ${SRC_PATH_render}/render.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

# compile the thread project with position independence code
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(render STATIC ${SRC_FILE_LIST})

set(LINK_FILE_LIST
  base
  GL
  )
target_link_libraries(render ${LINK_FILE_LIST})

# build dependicies
set(DEP_PROJ_LIST
  base
  )
add_dependencies(render ${DEP_PROJ_LIST})
