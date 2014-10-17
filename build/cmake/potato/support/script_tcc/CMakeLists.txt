cmake_minimum_required(VERSION 2.8)

project(script)

set(SRC_PATH_script ${SRC_PATH_support}/script_tcc)

set(INC_PATH_LIST
  ${SRC_PATH_potato}
  ${SRC_PATH_potato}/engine
  ${CODE_PATH}/external/tinycc
  ${SRC_PATH_script}
  )

set(SRC_FILE_LIST_base
  ${SRC_PATH_support}/../engine/script.h
  ${SRC_PATH_script}/script_impl.h
  ${SRC_PATH_script}/script.cpp
  )
  
if(OS_IS_LINUX)
set(SRC_FILE_LIST
  ${SRC_FILE_LIST_base}
  )
elseif(OS_IS_WINDOWS)
set(SRC_FILE_LIST
  ${SRC_FILE_LIST_base}
  ${SRC_PATH_script}/script_tcc.def
  )
endif()

source_group("source" FILES ${SRC_FILE_LIST})

set(LIBRARY_OUTPUT_PATH ${OUT_PATH}/bin)

include_directories(${INC_PATH_LIST})

add_library(script SHARED ${SRC_FILE_LIST})


if(OS_IS_LINUX)
set(LINK_FILE_LIST
  tinycc
  )
elseif(OS_IS_WINDOWS)
  if(BUILD_DEBUG)
    set(LINK_FILE_LIST
      ${OUT_PATH}/lib/Debug/tinycc.lib
      )
  elseif(BUILD_MINSIZEREL)
    set(LINK_FILE_LIST
      ${OUT_PATH}/lib/MinSizeRel/tinycc.lib
      )
  elseif(BUILD_RELEASE)
    set(LINK_FILE_LIST
      ${OUT_PATH}/lib/Release/tinycc.lib
      )
  elseif(BUILD_RELWITHDEBINFO)
    set(LINK_FILE_LIST
      ${OUT_PATH}/lib/RelWithDebInfo/tinycc.lib
      )
  endif()
endif()
target_link_libraries(script ${LINK_FILE_LIST})

add_dependencies(script tinycc)
