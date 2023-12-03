cmake_minimum_required(VERSION 3.26)
project(animation)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Code/C++/qt6/qt6-static/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        REQUIRED)

include_directories(src)

add_executable(animation main.cpp
        src/mainwindow/mainwindow.hpp
        src/mainwindow/mainwindow.ui
        src/animated_button.hpp
        src/easing_function.hpp)

target_link_libraries(animation
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts
)

file(COPY
        src/animated_button.hpp
        DESTINATION ${PROJECT_NAME}_autogen/include)
