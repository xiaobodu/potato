cmake_minimum_required(VERSION 2.8)

project(render_gles)

set(SRC_PATH_render_gles ${SRC_PATH_support}/render_gles)

set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_potato}/engine
  ${SRC_PATH_render_gles}
  ${CODE_PATH}/external/rapidjson/include
  )

set(SRC_FILE_LIST
  ${SRC_PATH_render_gles}/render_gles.h
  ${SRC_PATH_render_gles}/render_gles.cpp
  ${SRC_PATH_render_gles}/canvas_gles.h
  ${SRC_PATH_render_gles}/canvas_gles.cpp
  ${SRC_PATH_render_gles}/transform_gles.h
  ${SRC_PATH_render_gles}/transform_gles.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(render_gles SHARED ${SRC_FILE_LIST})

set(LINK_FILE_LIST
  EGL
  GLESv1_CM
  )
target_link_libraries(render_gles ${LINK_FILE_LIST})
