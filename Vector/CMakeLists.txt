cmake_minimum_required(VERSION 3.10)

project(Vector)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Vector 
    VectorSource/main.cpp 
    VectorHeaders/Vector.h 
    VectorHeaders/Vector.hpp
    VectorHeaders/allocator.h
    VectorHeaders/allocator.hpp
    VectorHeaders/construct_at.hpp
)