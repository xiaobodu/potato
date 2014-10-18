cmake_minimum_required(VERSION 2.8)

project(display)

set(SRC_PATH_display ${SRC_PATH_support}/display_windows_gles)

set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_potato}/engine
  ${SRC_PATH_display}
  )

set(SRC_FILE_LIST_base
  ${SRC_PATH_potato}/engine/input.h
  ${SRC_PATH_potato}/engine/input.cpp
  ${SRC_PATH_potato}/engine/sensor.h
  ${SRC_PATH_potato}/engine/sensor.cpp
  ${SRC_PATH_display}/display_impl.h
  ${SRC_PATH_display}/display.cpp
  ${SRC_PATH_display}/display.def
  ${SRC_PATH_potato}/utility/file.h
  ${SRC_PATH_potato}/utility/log.h
  )
  
if(OS_IS_LINUX)
set(SRC_FILE_LIST
  ${SRC_FILE_LIST_base}
  )
elseif(OS_IS_WINDOWS)
set(SRC_FILE_LIST
  ${SRC_FILE_LIST_base}
  ${SRC_PATH_display}/display.def
  )
endif()

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH ${OUT_PATH}/bin)

include_directories(${INC_PATH_LIST})

add_definitions(-DC4G_API_EXPORT)

add_library(display SHARED ${SRC_FILE_LIST})

set(LINK_FILE_LIST
  opengl32
  )
target_link_libraries(display ${LINK_FILE_LIST})
