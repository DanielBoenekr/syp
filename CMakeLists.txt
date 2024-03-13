cmake_minimum_required(VERSION 3.22)
project(Save_your_plants)

set(CMAKE_CXX_STANDARD 17)

add_executable(Save_your_plants main.cpp
        window_settings.h
        window_settings.cpp)

if(WIN32)
    target_link_libraries(Save_your_plants PRIVATE user32)
endif()
