cmake_minimum_required(VERSION 2.8)

project(engine)

set(SRC_PATH_engine ${SRC_PATH_potato}/engine)

set(INC_PATH_LIST
  ${INC_PATH_potato}
  ${SRC_PATH_engine}
  ${CODE_PATH}/external/rapidjson/include
  )

set(SRC_FILE_LIST
  ${SRC_PATH_engine}/base.h
  ${SRC_PATH_engine}/display.h
  ${SRC_PATH_engine}/render.h
  ${SRC_PATH_engine}/asset.h
  ${SRC_PATH_engine}/scene.h
  ${SRC_PATH_engine}/engine.h
  ${SRC_PATH_engine}/engine.cpp
  ${SRC_PATH_potato}/utility/thread.h
  ${SRC_PATH_potato}/utility/thread.cpp
  ${SRC_PATH_potato}/utility/sharedlibrary.h
  ${SRC_PATH_potato}/utility/sharedlibrary.cpp
  ${SRC_PATH_potato}/utility/file.h
  ${SRC_PATH_potato}/utility/log.h
  )

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

include_directories(${INC_PATH_LIST})

add_library(engine SHARED ${SRC_FILE_LIST})

set(LINK_FILE_LIST
  potato
  pthread
  dl
  )
target_link_libraries(engine ${LINK_FILE_LIST})

# build dependicies
set(DEP_PROJ_LIST
  potato
  )
add_dependencies(engine ${DEP_PROJ_LIST})
