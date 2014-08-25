cmake_minimum_required(VERSION 2.8)

project(display)

set(SRC_PATH_display ${SRC_PATH_potato}/display)

set(INC_PATH_LIST
  ${SRC_PATH_display}
  )

set(RC_FILE_LIST
  ${SRC_PATH_display}/display.h
  ${SRC_PATH_display}/display.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

# compile the thread project with position independence code
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(display STATIC ${SRC_FILE_LIST})

set(LINK_FILE_LIST
  base
  )
target_link_libraries(display ${LINK_FILE_LIST})

# build dependicies
set(DEP_PROJ_LIST
  base
  )
add_dependencies(display ${DEP_PROJ_LIST})
