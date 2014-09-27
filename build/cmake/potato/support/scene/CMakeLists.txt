cmake_minimum_required(VERSION 2.8)

project(scene)

set(SRC_PATH_scene ${SRC_PATH_support}/scene)

add_definitions(-DC4G_API_EXPORT)

set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_potato}/engine
  ${SRC_PATH_scene}
  ${CODE_PATH}/external/rapidjson/include
  )

set(SRC_FILE_LIST_base
  ${SRC_PATH_support}/../engine/scene.h
  ${SRC_PATH_scene}/scene_base.h
  ${SRC_PATH_scene}/scene_impl.h
  ${SRC_PATH_scene}/scene.cpp
  ${SRC_PATH_scene}/builder.h
  ${SRC_PATH_scene}/builder.cpp
  ${SRC_PATH_scene}/layout.h
  ${SRC_PATH_scene}/layout.cpp
  ${SRC_PATH_scene}/widget.h
  ${SRC_PATH_scene}/widget.cpp
  ${SRC_PATH_scene}/panel.h
  ${SRC_PATH_scene}/panel.cpp
  ${SRC_PATH_scene}/image.h
  ${SRC_PATH_scene}/image.cpp
  ${SRC_PATH_scene}/flip.h
  ${SRC_PATH_scene}/flip.cpp
  ${SRC_PATH_scene}/process.cpp
  ${SRC_PATH_potato}/engine/input.h
  ${SRC_PATH_potato}/engine/input.cpp
  ${SRC_PATH_potato}/engine/sensor.h
  ${SRC_PATH_potato}/engine/sensor.cpp
  ${SRC_PATH_potato}/utility/mathematics.h
  ${SRC_PATH_potato}/utility/mathematics.cpp
  ${SRC_PATH_potato}/utility/file.h
  ${SRC_PATH_potato}/utility/log.h
  ${SRC_PATH_potato}/utility/sharedlibrary.h
  ${SRC_PATH_potato}/utility/sharedlibrary.cpp
  )
  
if(OS_IS_LINUX)
set(SRC_FILE_LIST
  ${SRC_FILE_LIST_base}
  )
elseif(OS_IS_WINDOWS)
set(SRC_FILE_LIST
  ${SRC_FILE_LIST_base}
  ${SRC_PATH_scene}/scene.def
  )
endif()

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(scene SHARED ${SRC_FILE_LIST})

if(OS_IS_LINUX)
set(LINK_FILE_LIST
  dl
  )
endif()
target_link_libraries(scene ${LINK_FILE_LIST})
