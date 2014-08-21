CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT (potato)

IF ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  SET (OS_IS_LINUX TRUE)
ELSEIF ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  SET (OS_IS_WINDOWS TRUE)
ELSE ()
  MESSAGE (FATAL_ERROR "Sorry, don't support your system - ${CMAKE_SYSTEM_NAME}")
ENDIF ()

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  SET (CXX_GNU TRUE)
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  SET (CXX_MSVC TRUE)
ELSE ()
  MESSAGE (FATAL_ERROR "Sorry, don't support your compiler - ${CMAKE_CXX_COMPILER_ID}")
ENDIF ()


#ADD_SUBDIRECTORY ()
~                                                                                    
~                                                                                    
~                                                                                    
~                
