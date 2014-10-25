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
elseif(OS_IS_LINUX)
#  set(CMAKE_C_FLAGS "-fPIC")
#  set(CMAKE_CXX_FLAGS "-fPIC")
endif()

add_definitions(-DLIBR_PATH="${ROOT_PATH}/out")
add_definitions(-DDATA_PATH="${ROOT_PATH}/data")
if(CXX_GCC)
  add_definitions(-DQT_OPENGL_ES)
elseif(CXX_MSVC)
  #add_definitions(-DQT_OPENGL_ES -DQT_NO_OPENGL_ES -DQT_OPENGL_ES_2 -DQT_NO_OPENGL_ES_2)
endif()
add_definitions(-DQT_OPENGL_LIB -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB)

#add_definitions(-DC4G_API_IMPORT)

set(INC_PATH_LIST_base
  ${QT_SDK_INC_PATH}
  ${CODE_PATH}/potato/src
  ${CODE_PATH}/potato/src/engine
  ${CODE_PATH}/potato/src/support/render_gles
  ${CODE_PATH}/potato/src/support/scene
  ${CODE_PATH}/external/rapidjson/include
  ${CODE_PATH_editor}/qt
  )

if(CXX_GNU)
set(INC_PATH_LIST
  ${INC_PATH_LIST_base}
  )
elseif(CXX_MSVC)
set(INC_PATH_LIST
  ${INC_PATH_LIST_base}
  ${QT_SDK_INC_PATH}/QtANGLE
  )
endif()

set(SRC_FILE_LIST
  ${CODE_PATH_editor}/editor.h
  ${CODE_PATH_editor}/editor.cpp
  ${CODE_PATH_editor}/editor_moc.cpp
  ${CODE_PATH_editor}/editor_mainwindow_ui.h
  ${CODE_PATH_editor}/qt/qgleswidget.h
  ${CODE_PATH_editor}/qt/qgleswidget.cpp
  ${CODE_PATH_editor}/qt/qgleswidget_moc.cpp
  ${CODE_PATH_editor}/qt/qsidebarwidget_ui.h
  ${CODE_PATH_editor}/qt/qsidebarwidget.h
  ${CODE_PATH_editor}/qt/qsidebarwidget.cpp
  ${CODE_PATH_editor}/qt/qsidebarwidget_moc.cpp
  ${CODE_PATH_editor}/qt/qpropertywidget_ui.h
  ${CODE_PATH_editor}/qt/qpropertywidget.h
  ${CODE_PATH_editor}/qt/qpropertywidget.cpp
  ${CODE_PATH_editor}/qt/qpropertywidget_moc.cpp
  ${CODE_PATH_editor}/qt/qbasicpropertywidget_ui.h
  ${CODE_PATH_editor}/qt/qbasicpropertywidget.h
  ${CODE_PATH_editor}/qt/qbasicpropertywidget.cpp
  ${CODE_PATH_editor}/qt/qbasicpropertywidget_moc.cpp
  ${CODE_PATH_editor}/qt/qimagepropertywidget_ui.h
  ${CODE_PATH_editor}/qt/qimagepropertywidget.h
  ${CODE_PATH_editor}/qt/qimagepropertywidget.cpp
  ${CODE_PATH_editor}/qt/qimagepropertywidget_moc.cpp
  ${CODE_PATH_editor}/qt/qrectfpropertywidget_ui.h
  ${CODE_PATH_editor}/qt/qrectfpropertywidget.h
  ${CODE_PATH_editor}/qt/qrectfpropertywidget.cpp
  ${CODE_PATH_editor}/qt/qrectfpropertywidget_moc.cpp
  ${CODE_PATH_editor}/qt/qscenetreewidget.h
  ${CODE_PATH_editor}/qt/qscenetreewidget.cpp
  ${CODE_PATH_editor}/qt/qscenetreewidget_moc.cpp
  ${CODE_PATH_editor}/qt/qaboutdialog_ui.h
  ${CODE_PATH_editor}/qt/qaboutdialog.h
  ${CODE_PATH_editor}/qt/qaboutdialog.cpp
  ${CODE_PATH_editor}/qt/qaboutdialog_moc.cpp
  ${CODE_PATH}/potato/src/engine/input.h
  ${CODE_PATH}/potato/src/engine/input.cpp
  ${CODE_PATH}/potato/src/utility/sharedlibrary.h
  ${CODE_PATH}/potato/src/utility/sharedlibrary.cpp
  )

include_directories(${INC_PATH_LIST})

set(LINK_PATH_LIST_base
  ${OUT_PATH}/bin
  )

if(OS_IS_WINDOWS)
set(LINK_PATH_LIST
  ${LINK_PATH_LIST_base}
  ${QT_SDK_PATH}/lib
  )
elseif(OS_IS_LINUX)
set(LINK_PATH_LIST
  ${LINK_PATH_LIST_base}
  #${QT_SDK_PATH}/lib/x86_64-linux-gnu
  )
endif()

link_directories(${LINK_PATH_LIST})


source_group("source" FILES ${SRC_FILE_LIST})

set(EXECUTABLE_OUTPUT_PATH ${OUT_PATH}/bin)

add_executable(editor ${SRC_FILE_LIST})


if(OS_IS_WINDOWS)
set(LINK_FILE_LIST
#  render.lib
#  scene.lib
  qtmain.lib
  Qt5Core.lib
  Qt5Gui.lib
  Qt5Widgets.lib
  Qt5OpenGL.lib
  opengl32.lib
  )
elseif(OS_IS_LINUX)
set(LINK_FILE_LIST
  dl
  png
#  render
#  scene
  Qt5Core
  Qt5Gui
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
QT_GENERATE_MOC(${CODE_PATH_editor}/qt qsidebarwidget)
QT_GENERATE_MOC(${CODE_PATH_editor}/qt qpropertywidget)
QT_GENERATE_MOC(${CODE_PATH_editor}/qt qbasicpropertywidget)
QT_GENERATE_MOC(${CODE_PATH_editor}/qt qimagepropertywidget)
QT_GENERATE_MOC(${CODE_PATH_editor}/qt qrectfpropertywidget)
QT_GENERATE_MOC(${CODE_PATH_editor}/qt qscenetreewidget)
QT_GENERATE_MOC(${CODE_PATH_editor}/qt qaboutdialog)


macro(QT_GENERATE_UIC directory resname filepath filename)
add_custom_target(${filename}_ui_h
  DEPENDS ${directory}/${filepath}/${filename}_ui.h
  VERBATIM)
add_custom_command(OUTPUT ${directory}/${filepath}/${filename}_ui.h
  DEPENDS ${directory}/res/${resname}.ui
  COMMAND ${QT_SDK_PATH}/bin/uic ${directory}/res/${resname}.ui -o ${directory}/${filepath}/${filename}_ui.h
  COMMENT "Generating C++ header file ${directory}/${filepath}/${filename}_ui.h by ${directory}/res/${resname}.ui"
  VERBATIM)
endmacro(QT_GENERATE_UIC)

QT_GENERATE_UIC(${CODE_PATH_editor} mainwindow . editor_mainwindow)
QT_GENERATE_UIC(${CODE_PATH_editor} sidebarwidget qt qsidebarwidget)
QT_GENERATE_UIC(${CODE_PATH_editor} propertywidget qt qpropertywidget)
QT_GENERATE_UIC(${CODE_PATH_editor} basicpropertywidget qt qbasicpropertywidget)
QT_GENERATE_UIC(${CODE_PATH_editor} rectfpropertywidget qt qrectfpropertywidget)
QT_GENERATE_UIC(${CODE_PATH_editor} imagepropertywidget qt qimagepropertywidget)
QT_GENERATE_UIC(${CODE_PATH_editor} aboutdialog qt qaboutdialog)

# build dependicies
set(DEP_PROJ_LIST
  render
  scene
  editor_moc_cpp
  editor_mainwindow_ui_h
  qgleswidget_moc_cpp
  qsidebarwidget_ui_h
  qsidebarwidget_moc_cpp
  qpropertywidget_ui_h
  qpropertywidget_moc_cpp
  qbasicpropertywidget_ui_h
  qbasicpropertywidget_moc_cpp
  qrectfpropertywidget_ui_h
  qrectfpropertywidget_moc_cpp
  qimagepropertywidget_ui_h
  qimagepropertywidget_moc_cpp
  qscenetreewidget_moc_cpp
  qaboutdialog_ui_h
  qaboutdialog_moc_cpp
  )
add_dependencies(editor ${DEP_PROJ_LIST})
