cmake_minimum_required(VERSION 3.10)

project(MyString)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(MyString 
    StringSrc/main.cpp 
    StringHeaders/myString.h 
    StringSrc/myString.hpp
    StringHeaders/allocator.h
    StringSrc/allocator.hpp
)