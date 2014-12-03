cmake_minimum_required(VERSION 2.8)

project(engine)

set(SRC_PATH_engine ${SRC_PATH_potato}/engine)

set(INC_PATH_LIST_base
  ${INC_PATH_potato}
  ${SRC_PATH_engine}
  )

if(OS_IS_LINUX)
  set(INC_PATH_LIST
    ${INC_PATH_LIST_base}
    )
elseif(OS_IS_WINDOWS)
  set(INC_PATH_LIST
    ${INC_PATH_LIST_base}
    ${OUT_PATH}/pthreads-w32-2-9-1-release/Pre-built.2/include
    )
endif()

set(SRC_FILE_LIST_base
  ${SRC_PATH_engine}/base.h
  ${SRC_PATH_engine}/display.h
  ${SRC_PATH_engine}/render.h
  ${SRC_PATH_engine}/asset.h
  ${SRC_PATH_engine}/scene.h
  ${SRC_PATH_engine}/engine.h
  ${SRC_PATH_engine}/engine.cpp
  ${SRC_PATH_potato}/utility/thread.h
  ${SRC_PATH_potato}/utility/thread.cpp
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
  ${SRC_PATH_engine}/engine.def
  )
endif()

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH ${OUT_PATH}/bin)

include_directories(${INC_PATH_LIST})

add_library(engine SHARED ${SRC_FILE_LIST})

if(OS_IS_LINUX)
set(LINK_FILE_LIST
  dl
  )
elseif(OS_IS_WINDOWS)
set(LINK_FILE_LIST
  )
endif()
target_link_libraries(engine ${LINK_FILE_LIST})

# build dependicies
set(DEP_PROJ_LIST
  potato
  )
add_dependencies(engine ${DEP_PROJ_LIST})
