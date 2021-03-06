cmake_minimum_required(VERSION 2.8)

project(demo)

set(CODE_PATH_demo ${CODE_PATH}/demo)

set(INC_PATH_LIST
  ${CODE_PATH}/potato/inc
  ${CODE_PATH_demo}
  )
include_directories(${INC_PATH_LIST})

set(CODE_FILE_LIST
  ${CODE_PATH_demo}/demo.h
  ${CODE_PATH_demo}/demo.cpp
  )
source_group("source" FILES ${CODE_FILE_LIST})

set(LINK_PATH_LIST
  ${OUT_PATH}/bin
  ${OUT_PATH}/lib
  )
link_directories(${LINK_PATH_LIST})

set(EXECUTABLE_OUTPUT_PATH ${OUT_PATH}/bin)

add_definitions(-DAPP_NAME="demo")

add_executable(demo ${CODE_FILE_LIST})

if(OS_IS_LINUX OR OS_IS_DARWIN)
set(LINK_FILE_LIST
  potato
  dl
  )
elseif(OS_IS_WINDOWS)
  if(BUILD_DEBUG)
    set(LINK_FILE_LIST
      ${OUT_PATH}/lib/Debug/potato.lib
      )
  else()
    set(LINK_FILE_LIST
      ${OUT_PATH}/lib/Release/potato.lib
      )
  endif()
endif()
target_link_libraries(demo ${LINK_FILE_LIST})

# build dependicies
set(DEP_PROJ_LIST
  potato
  engine
  display
  render
  asset
  scene
  flash
  script
  )
add_dependencies(demo ${DEP_PROJ_LIST})
