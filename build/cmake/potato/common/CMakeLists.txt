CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT (common)

SET (SRC_PATH_common ${SRC_PATH_potato}/common)

SET (INC_PATH_LIST
  ${SRC_PATH_common}
  )

SET (SRC_FILE_LIST
  ${SRC_PATH_common}/common.h
  ${SRC_PATH_common}/common.cpp
  ${SRC_PATH_common}/dynamiclibrary.h
  ${SRC_PATH_common}/dynamiclibrary.cpp
  )

SOURCE_GROUP ("source" FILES ${SRC_FILE_LIST})

SET (LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

INCLUDE_DIRECTORIES (${INC_PATH_LIST})

ADD_LIBRARY (common STATIC ${SRC_FILE_LIST})


