CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT (all)

# define/check environment
IF ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  SET (OS_IS_LINUX TRUE)
  add_definitions(-DOS_IS_LINUX)
ELSEIF ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  SET (OS_IS_WINDOWS TRUE)
  add_definitions(-DOS_IS_WINDOWS)
ELSE ()
  MESSAGE (FATAL_ERROR "Sorry, don't support your system - ${CMAKE_SYSTEM_NAME}")
ENDIF ()

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  SET (CXX_GNU TRUE)
  add_definitions(-DCXX_GNU)
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  SET (CXX_MSVC TRUE)
  add_definitions(-DCXX_MSVC)
ELSE ()
  MESSAGE (FATAL_ERROR "Sorry, don't support your compiler - ${CMAKE_CXX_COMPILER_ID}")
ENDIF ()

# define path
SET (ROOT_PATH "${all_SOURCE_DIR}/../..")
SET (CODE_PATH "${ROOT_PATH}/code")
SET (OUT_PATH "${ROOT_PATH}/out")

# add sub-project
ADD_SUBDIRECTORY (potato)

ADD_SUBDIRECTORY (test)

