cmake_minimum_required(VERSION 2.8)

project(asset)

set(SRC_PATH_asset ${SRC_PATH_support}/asset)

if(OS_IS_LINUX)
set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_potato}/engine
  ${SRC_PATH_asset}
  )
elseif(OS_IS_WINDOWS)
set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_potato}/engine
  ${CODE_PATH}/external/libpng
  ${SRC_PATH_asset}
  )
endif()

set(SRC_FILE_LIST
  ${SRC_PATH_support}/../engine/asset.h
  ${SRC_PATH_asset}/asset.cpp
  ${SRC_PATH_asset}/file_png.cpp
  )

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(asset SHARED ${SRC_FILE_LIST})

if(OS_IS_LINUX)
set(LINK_FILE_LIST
  png12
  z
  )
elseif(OS_IS_WINDOWS)
set(LINK_FILE_LIST
  libpng.lib
  zlib.lib
  )
endif()
target_link_libraries(asset ${LINK_FILE_LIST})

add_dependencies(asset png)
