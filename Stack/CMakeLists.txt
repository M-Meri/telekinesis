cmake_minimum_required(VERSION 3.10)

project(Stack)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
    StackHdr
    StackSrc
)

add_executable(Stack 
    StackSrc/stack.hpp
    StackSrc/main.cpp
)