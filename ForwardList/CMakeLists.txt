cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

project(Forward_List)

add_executable(Forward_List
    Forward_List_Headers/forward_list.hpp
    Forward_List_Headers/forward_list.h
    Forward_List_Sources/main.cpp
)