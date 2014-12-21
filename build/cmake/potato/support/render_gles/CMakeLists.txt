cmake_minimum_required(VERSION 2.8)

project(render)

set(SRC_PATH_render ${SRC_PATH_support}/render_gles)

add_definitions(-DC4G_API_EXPORT)

set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_potato}/engine
  ${SRC_PATH_render}
  ${CODE_PATH}/external/rapidjson/include
  ${CODE_PATH}/external/glm
  )

set(SRC_FILE_LIST_base
  ${SRC_PATH_render}/render_impl.h
  ${SRC_PATH_render}/render.cpp
  ${SRC_PATH_render}/camera.h
  ${SRC_PATH_render}/camera.cpp
  ${SRC_PATH_render}/canvas.h
  ${SRC_PATH_render}/canvas.cpp
  ${SRC_PATH_render}/space.h
  ${SRC_PATH_render}/space.cpp
  ${SRC_PATH_render}/transform.h
  ${SRC_PATH_render}/transform.cpp
  ${SRC_PATH_render}/blend.h
  ${SRC_PATH_render}/blend.cpp
  )
  
if(OS_IS_LINUX)
set(SRC_FILE_LIST
  ${SRC_FILE_LIST_base}
  )
elseif(OS_IS_WINDOWS)
set(SRC_FILE_LIST
  ${SRC_FILE_LIST_base}
  ${SRC_PATH_render}/render.def
  )
endif()

source_group("source" FILES ${SRC_FILE_LIST})

set(SRC_FILE_LIST_other
  ${SRC_PATH_potato}/utility/mathematics.h
  ${SRC_PATH_potato}/utility/mathematics.cpp
  )

source_group("other" FILES ${SRC_FILE_LIST_other})

set(LIBRARY_OUTPUT_PATH ${OUT_PATH}/bin)

include_directories(${INC_PATH_LIST})

add_definitions(-DC4G_API_EXPORT)

add_library(render SHARED
  ${SRC_FILE_LIST}
  ${SRC_FILE_LIST_other}
  )

if(OS_IS_LINUX)
set(LINK_FILE_LIST
  GLESv1_CM
  )
elseif(OS_IS_WINDOWS)
set(LINK_FILE_LIST
  opengl32.lib
  )
endif()

target_link_libraries(render ${LINK_FILE_LIST})
