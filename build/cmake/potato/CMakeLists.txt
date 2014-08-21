CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT (potato)

SET (CODE_PATH_potato ${CODE_PATH}/potato)

SET (INC_PATH_potato "${CODE_PATH_potato}/inc")
SET (SRC_PATH_potato "${CODE_PATH_potato}/src")

# add sub-project
ADD_SUBDIRECTORY (common)

SET (INC_PATH_LIST
  ${INC_PATH_potato}
  ${SRC_PATH_potato}
  )

SET (SRC_FILE_LIST
  ${INC_PATH_potato}/potato.h
  ${SRC_PATH_potato}/potato.cpp
  )

SOURCE_GROUP ("source" FILES ${SRC_FILE_LIST})

SET (LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

INCLUDE_DIRECTORIES (${INC_PATH_LIST})

ADD_LIBRARY (potato STATIC ${SRC_FILE_LIST})

# build dependicies
SET (DEP_PROJ_LIST
  common
  )

ADD_DEPENDENCIES (potato ${DEP_PROJ_LIST})

