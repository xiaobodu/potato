cmake_minimum_required(VERSION 2.8)

project(support)

set(SRC_PATH_support ${SRC_PATH_potato}/support)

if (OS_IS_LINUX)
add_subdirectory(display_linux_gles)
endif()

add_subdirectory(render_gles)

add_subdirectory(asset)

add_subdirectory(scene)

add_subdirectory(script_tcc)
