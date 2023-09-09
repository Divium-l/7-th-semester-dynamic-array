cmake_minimum_required(VERSION 3.26)
project(Dyn)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(Dyn
        dynamic_array.hpp
        main.cpp)
