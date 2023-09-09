set(PROJECT_NAME "Dyn")
set(EXECUTABLE_NAME "Dyn")

cmake_minimum_required(VERSION 3.26)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_subdirectory(test)

add_executable(${EXECUTABLE_NAME}
        dynamic_array.hpp
        main.cpp)