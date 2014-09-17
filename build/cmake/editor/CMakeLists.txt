cmake_minimum_required(VERSION 2.8)

project(editor)

set(CODE_PATH_editor ${CODE_PATH}/editor)

set(QT_SDK_PATH "${QT_SDK_PATH}" CACHE STRING "Add the Qt SDK path" FORCE)
if(OS_IS_WINDOWS)
  set(QT_SDK_INC_PATH ${QT_SDK_PATH}/include)
elseif(OS_IS_LINUX)
  set(QT_SDK_INC_PATH ${QT_SDK_PATH}/include/qt5)
endif()


if(OS_IS_WINDOWS)
  set(CMAKE_CXX_FLAGS "/fPIC")
elif(OS_IS_LINUX)
  set(CMAKE_C_FLAGS "-fPIC")
  set(CMAKE_CXX_FLAGS "-fPIC")
endif()

add_definitions(-DLIBR_PATH="${ROOT_PATH}/out")
add_definitions(-DDATA_PATH="${ROOT_PATH}/data")
add_definitions(-DQT_OPENGL_ES -DQT_OPENGL_LIB -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB)

set(INC_PATH_LIST
  ${QT_SDK_INC_PATH}
  ${CODE_PATH}/potato/src
  ${CODE_PATH}/potato/src/engine
  ${CODE_PATH}/potato/src/support/render_gles
  ${CODE_PATH}/potato/src/support/scene
  ${CODE_PATH_editor}/qt
  )

set(SRC_FILE_LIST
  ${CODE_PATH_editor}/editor.h
  ${CODE_PATH_editor}/editor.cpp
  ${CODE_PATH_editor}/editor_moc.cpp
  ${CODE_PATH_editor}/editor_mainwindow_ui.h
  ${CODE_PATH_editor}/qt/qgleswidget.h
  ${CODE_PATH_editor}/qt/qgleswidget.cpp
  ${CODE_PATH_editor}/qt/qgleswidget_moc.cpp
  ${CODE_PATH}/potato/src/engine/input.h
  ${CODE_PATH}/potato/src/engine/input.cpp
  )

include_directories(${INC_PATH_LIST})


if(OS_IS_WINDOWS)
set(LINK_PATH_LIST
  ${OUT_PATH}/bin
  ${OUT_PATH}/lib
  ${QT_SDK_PATH}/lib
  )
elseif(OS_IS_LINUX)
set(LINK_PATH_LIST
  ${OUT_PATH}/bin
  ${OUT_PATH}/lib
  #${QT_SDK_PATH}/lib/x86_64-linux-gnu
  )
endif()

link_directories(${LINK_PATH_LIST})


source_group("source" FILES ${SRC_FILE_LIST})

set(EXECUTABLE_OUTPUT_PATH ${OUT_PATH}/bin)

add_executable(editor ${SRC_FILE_LIST})


if(OS_IS_WINDOWS)
set(LINK_FILE_LIST
  qtmain.lib
  Qt5Core.lib
  Qt5Gui.lib
  Qt5Widgets.lib
  Qt5OpenGL.lib
  )
elseif(OS_IS_LINUX)
set(LINK_FILE_LIST
  png
  render_gles
  scene
  Qt5Core
  Qt5Widgets
  Qt5OpenGL
  EGL
  GLESv1_CM
  )
endif()
target_link_libraries(editor ${LINK_FILE_LIST})


macro(QT_GENERATE_MOC directory filename)
add_custom_target(${filename}_moc_cpp
  DEPENDS ${directory}/${filename}_moc.cpp
  VERBATIM)
add_custom_command(OUTPUT ${directory}/${filename}_moc.cpp
  DEPENDS ${directory}/${filename}.h
  COMMAND ${QT_SDK_PATH}/bin/moc ${directory}/${filename}.h -o ${directory}/${filename}_moc.cpp -DQT_CORE_LIB -DQT_DLL -DQT_GUI_LIB -DQT_WIDGETS_LIB -DUNICODE -I${QT_SDK_INC_PATH} -I${QT_SDK_INC_PATH}/QtCore -I${QT_SDK_INC_PATH}/QtGui -I${QT_SDK_INC_PATH}/QtWidgets
  COMMENT "Generating C++ source file ${directory}/${filename}_moc.cpp by ${directory}/${filename}.h"
  VERBATIM)
endmacro(QT_GENERATE_MOC)

QT_GENERATE_MOC(${CODE_PATH_editor} editor)
QT_GENERATE_MOC(${CODE_PATH_editor}/qt qgleswidget)


macro(QT_GENERATE_UIC directory resname filename)
add_custom_target(${filename}_ui_h
  DEPENDS ${directory}/${filename}_ui.h
  VERBATIM)
add_custom_command(OUTPUT ${directory}/${filename}_ui.h
  DEPENDS ${directory}/res/${resname}.ui
  COMMAND ${QT_SDK_PATH}/bin/uic ${directory}/res/${resname}.ui -o ${directory}/${filename}_ui.h
  COMMENT "Generating C++ header file ${directory}/${filename}_ui.h by ${directory}/res/${resname}.ui"
  VERBATIM)
endmacro(QT_GENERATE_UIC)

QT_GENERATE_UIC(${CODE_PATH_editor} mainwindow editor_mainwindow)

# build dependicies
set(DEP_PROJ_LIST
  render_gles
  scene
  editor_moc_cpp
  editor_main_ui_h
  qgleswidget_moc_cpp
  )
add_dependencies(editor ${DEP_PROJ_LIST})
