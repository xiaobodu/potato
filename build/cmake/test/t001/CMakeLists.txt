CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT (t001)

SET (CODE_PATH_t001 ${CODE_PATH_test}/t001)

SET (INC_PATH_LIST
  ${CODE_PATH}/potato/inc
  ${CODE_PATH_t001}
  )
INCLUDE_DIRECTORIES (${INC_PATH_LIST})

SET (CODE_FILE_LIST
  ${CODE_PATH_t001}/t001.h
  ${CODE_PATH_t001}/t001.cpp
  )
SOURCE_GROUP ("source" FILES ${CODE_FILE_LIST})

SET (LINK_PATH_LIST
  ${OUT_PATH}/bin
  ${OUT_PATH}/lib
  )
link_directories(${LINK_PATH_LIST})

set(EXECUTABLE_OUTPUT_PATH ${OUT_PATH}/bin)

add_definitions(-DLIBR_PATH="${ROOT_PATH}/out")
add_definitions(-DDATA_PATH="${ROOT_PATH}/data")

ADD_EXECUTABLE (t001 ${CODE_FILE_LIST})

if(OS_IS_LINUX)
set(LINK_FILE_LIST
  potato
  dl
  )
elseif(OS_IS_WINDOWS)
set(LINK_FILE_LIST
  ${OUT_PATH}/lib/Release/potato.lib
  )
endif()
target_link_libraries(t001 ${LINK_FILE_LIST})

# build dependicies
SET (DEP_PROJ_LIST
  potato
  )
add_dependencies(t001 ${DEP_PROJ_LIST})
