cmake_minimum_required(VERSION 3.10)

project(Queue)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
    QueueHdr
    QueueSrc
)

add_executable(Queue
    QueueSrc/queue.hpp
    QueueSrc/main.cpp
)