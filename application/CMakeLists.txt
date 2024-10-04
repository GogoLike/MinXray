# Find Qt
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOUIC ON)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

add_executable(min-xray ${PROJECT_SOURCES})
target_link_libraries(min-xray PRIVATE Qt6::Core Qt6::Widgets)