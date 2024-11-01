cmake_minimum_required(VERSION 3.5)

project(tetris_desktop VERSION 2.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR YES)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        ../brick_game/tetris/tetris_back.cpp
        ../brick_game/tetris/tetris_back.h
        ../controller/controller.cpp
        ../controller/controller.h
        ../gui/desktop/mainwindow.cpp
        ../gui/desktop/mainwindow.h
        ../main_qt.cpp
)


#  определение TARGET
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tetris_desktop MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(tetris_desktop 
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(tetris_desktop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

#  свойства проекта
set_target_properties(tetris_desktop PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

#  установка
install(TARGETS tetris_desktop
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Финализация Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tetris_desktop)
endif()