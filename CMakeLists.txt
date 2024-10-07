cmake_minimum_required(VERSION 3.16.0)

project(min-xray VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOUIC ON)

set(PROJECT_SOURCES
        application/main.cpp
        application/mainwindow.cpp
        application/mainwindow.h
        application/mainwindow.ui
)

add_executable(min-xray ${PROJECT_SOURCES})
target_link_libraries(min-xray PRIVATE Qt6::Core Qt6::Widgets)

# cppcheck
find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)

add_custom_target(cppcheck
        COMMAND ${CMAKE_CXX_CPPCHECK}
        --enable=all
        --std=c++17
        --library=qt.cfg
        --suppress=missingIncludeSystem
        --quiet
        ${CMAKE_SOURCE_DIR}/${PROJECT_SOURCES}
)