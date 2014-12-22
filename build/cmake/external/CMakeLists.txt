cmake_minimum_required(VERSION 2.8)

project(external)

set(CODE_PATH_external ${CODE_PATH}/external)

add_subdirectory("./libpng")

add_subdirectory(tinycc)
