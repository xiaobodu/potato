cmake_minimum_required(VERSION 2.4.3)

project(tinycc C)

set(CODE_PATH_tinycc ${CODE_PATH_external}/tinycc)

set(tinycc_sources
  ${CODE_PATH_tinycc}/tcc.c
  ${CODE_PATH_tinycc}/libtcc.c
  ${CODE_PATH_tinycc}/tccpp.c
  ${CODE_PATH_tinycc}/tccgen.c
  ${CODE_PATH_tinycc}/tccelf.c
  ${CODE_PATH_tinycc}/tccasm.c
  ${CODE_PATH_tinycc}/tccrun.c
  ${CODE_PATH_tinycc}/tcc.h
  ${CODE_PATH_tinycc}/config.h
  ${CODE_PATH_tinycc}/libtcc.h
  ${CODE_PATH_tinycc}/tcctok.h
  ${CODE_PATH_tinycc}/x86_64-gen.c
  ${CODE_PATH_tinycc}/i386-asm.c
  ${CODE_PATH_tinycc}/x86_64-asm.h
)

add_definitions(-DTCC_TARGET_X86_64)
add_definitions(-DWITHOUT_LIBTCC)

set(LIBRARY_OUTPUT_PATH "${OUT_PATH}/lib")

add_library(tinycc STATIC ${tinycc_sources})
