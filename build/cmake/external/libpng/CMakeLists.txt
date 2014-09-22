cmake_minimum_required(VERSION 2.4.3)

project(png C)

# needed packages
find_package(ZLIB REQUIRED)

set(CODE_PATH_libpng ${CODE_PATH_external}/libpng)

if(OS_IS_LINUX)
set(INC_PATH_LIST
  ${CODE_PATH_libpng}
  )
elseif(OS_IS_WINDOWS)
set(INC_PATH_LIST
  ${CODE_PATH_libpng}
  ${ROOT_PATH}/${ZLIB_INCLUDE_DIR}
  )
endif()

set(libpng_sources
  ${CODE_PATH_libpng}/png.h
  ${CODE_PATH_libpng}/pngconf.h
  ${CODE_PATH_libpng}/png.c
  ${CODE_PATH_libpng}/pngerror.c
  ${CODE_PATH_libpng}/pngget.c
  ${CODE_PATH_libpng}/pngmem.c
  ${CODE_PATH_libpng}/pngpread.c
  ${CODE_PATH_libpng}/pngread.c
  ${CODE_PATH_libpng}/pngrio.c
  ${CODE_PATH_libpng}/pngrtran.c
  ${CODE_PATH_libpng}/pngrutil.c
  ${CODE_PATH_libpng}/pngset.c
  ${CODE_PATH_libpng}/pngtrans.c
  ${CODE_PATH_libpng}/pngwio.c
  ${CODE_PATH_libpng}/pngwrite.c
  ${CODE_PATH_libpng}/pngwtran.c
  ${CODE_PATH_libpng}/pngwutil.c
)

add_definitions(-DPNG_CONFIGURE_LIBPNG)

add_definitions(-DLIBPNG_NO_MMX)
add_definitions(-DPNG_NO_MMX_CODE)
add_definitions(-DPNG_NO_FLOATING_POINT_SUPPORTED)

include_directories(${INC_PATH_LIST})

set(LIBRARY_OUTPUT_PATH
  ${OUT_PATH}/lib
  )

add_library(png STATIC ${libpng_sources})
