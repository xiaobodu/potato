cmake_minimum_required(VERSION 2.8)

project(render_gl)

set(SRC_PATH_render_gl ${SRC_PATH_support}/render_gl)

set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_potato}/engine
  ${SRC_PATH_render_gl}
  ${CODE_PATH}/external/rapidjson/include
  )

set(SRC_FILE_LIST
  ${SRC_PATH_render_gl}/render_gl.h
  ${SRC_PATH_render_gl}/render_gl.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(render_gl SHARED ${SRC_FILE_LIST})

set(LINK_FILE_LIST
  GL
  GLU
  )
target_link_libraries(render_gl ${LINK_FILE_LIST})
