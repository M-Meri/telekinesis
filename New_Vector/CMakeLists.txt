cmake_minimum_required(VERSION 3.10)

project(Vector)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
    VecHdr
    VecSrc
)

add_executable(Vector 
    VecSrc/main.cpp 
    VecSrc/vector.hpp
    VecSrc/allocator.hpp
)