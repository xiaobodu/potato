cmake_minimum_required(VERSION 2.8)

project(support)

set(SRC_PATH_support ${SRC_PATH_potato}/support)

if (OS_IS_LINUX)
add_subdirectory(display_linux_gles)
elseif (OS_IS_DARWIN)
add_subdirectory(display_darwin_gles)
elseif (OS_IS_WINDOWS)
add_subdirectory(display_windows_gles)
endif()

add_subdirectory(render_gles)

add_subdirectory(asset)

add_subdirectory(scene)

add_subdirectory(flash)

add_subdirectory(script_tcc)
