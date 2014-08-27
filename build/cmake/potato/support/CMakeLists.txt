cmake_minimum_required(VERSION 2.8)

project(support)

set(SRC_PATH_support ${SRC_PATH_potato}/support)

add_subdirectory(display_linux_gl)
add_subdirectory(display_linux_gles)
add_subdirectory(render_gl)
add_subdirectory(render_gles)
