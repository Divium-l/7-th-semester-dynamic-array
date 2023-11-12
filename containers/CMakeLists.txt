set(PROJECT_NAME "Containers")
set(EXECUTABLE_NAME "Containers")

cmake_minimum_required(VERSION 3.26)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_subdirectory(src)
add_subdirectory(test)