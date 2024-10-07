cmake_minimum_required(VERSION 3.16.0)

project(min-xray VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOUIC ON)

set(PROJECT_SOURCES
        application/main.cpp
        application/mainwindow.cpp
)

set(PROJECT_HEADERS
        application/mainwindow.h
)

set(PROJECT_UIS
        application/mainwindow.ui
)

add_executable(min-xray ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_UIS})
target_link_libraries(min-xray PRIVATE Qt6::Core Qt6::Widgets)

# CI PATH
foreach(ci_source ${PROJECT_SOURCES})
    get_filename_component(ci_source ${ci_source} ABSOLUTE)
    list(APPEND ci_sources ${ci_source})
endforeach()

foreach(ci_header ${PROJECT_HEADERS})
    get_filename_component(ci_header ${ci_header} ABSOLUTE)
    list(APPEND ci_sources ${ci_header})
endforeach()

# CppCheck
find_program(cppcheck_executable "cppcheck")

if(cppcheck_executable)
    set(CPPCHECK_EXECUTABLE ${cppcheck_executable})
else()
    message(FATAL_ERROR "CppCheck: ${CPPCHECK_EXECUTABLE} not found! Aborting")
endif()

add_custom_target(min-xray-cppcheck
    COMMAND
      ${CPPCHECK_EXECUTABLE}
      --enable=all
      --std=c++17
      --inline-suppr
      --quiet
      ${ci_sources}
    WORKING_DIRECTORY
      ${CMAKE_SOURCE_DIR}
    COMMENT
      "Check min-xray with ${CPPCHECK_EXECUTABLE} ..."
)

add_dependencies(min-xray min-xray-cppcheck)

# Clang-Format
find_program(clangformat_executable clang-format)

if(clangformat_executable)
    set(CLANGFORMAT_EXECUTABLE ${clangformat_executable})
else()
    message(FATAL_ERROR "ClangFormat: ${CLANGFORMAT_EXECUTABLE} not found! Aborting")
endif()

add_custom_target(min-xray-clangformat
    COMMAND
      ${CLANGFORMAT_EXECUTABLE}
      -style=Mozilla
      -i
      ${ci_sources}
    WORKING_DIRECTORY
      ${CMAKE_SOURCE_DIR}
    COMMENT
      "Formatting min-xray with ${CLANGFORMAT_EXECUTABLE} ..."
)

add_dependencies(min-xray min-xray-clangformat)