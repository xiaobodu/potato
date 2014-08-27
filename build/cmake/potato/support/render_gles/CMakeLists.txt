cmake_minimum_required(VERSION 2.8)

project(render_gles)

set(SRC_PATH_render_gles ${SRC_PATH_support}/render_gles)

set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_render_gles}
  )

set(SRC_FILE_LIST
  ${SRC_PATH_render_gles}/render_gles.h
  ${SRC_PATH_render_gles}/render_gles.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(render_gles SHARED ${SRC_FILE_LIST})

set(LINK_FILE_LIST
  base
  render
  EGL
  GLESv1_CM
  )
target_link_libraries(render_gles ${LINK_FILE_LIST})

# build dependicies
set(DEP_PROJ_LIST
  base
  render
  )
add_dependencies(render_gles ${DEP_PROJ_LIST})
