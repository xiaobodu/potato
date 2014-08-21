CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT (test)

SET (CODE_PATH_test ${CODE_PATH}/test)

SET (INC_PATH_LIST
  ${CODE_PATH}/potato/inc
  ${CODE_PATH_test}
  )
INCLUDE_DIRECTORIES (${INC_PATH_LIST})

SET (CODE_FILE_LIST
  ${CODE_PATH_test}/test.h
  ${CODE_PATH_test}/test.cpp
  )
SOURCE_GROUP ("source" FILES ${CODE_FILE_LIST})

SET (LINK_PATH_LIST
  ${OUT_PATH}/bin
  ${OUT_PATH}/lib
  )
link_directories(${LINK_PATH_LIST})

set(EXECUTABLE_OUTPUT_PATH ${OUT_PATH}/bin)

add_definitions(-DENGINE_FILE="$<TARGET_FILE:engine>")

ADD_EXECUTABLE (test ${CODE_FILE_LIST})

set(LINK_FILE_LIST
  potato
  dl
  )
target_link_libraries(test ${LINK_FILE_LIST})

# build dependicies
SET (DEP_PROJ_LIST
  potato
  )
ADD_DEPENDENCIES (test ${DEP_PROJ_LIST})
