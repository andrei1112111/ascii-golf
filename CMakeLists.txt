cmake_minimum_required(VERSION 3.30)
project(ascii_golf)

set(CMAKE_CXX_STANDARD 20)

add_executable(ascii_golf
        main.cpp
        graphics.cpp
        tragectory.cpp
        IO.cpp
)
