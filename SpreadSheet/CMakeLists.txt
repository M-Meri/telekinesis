cmake_minimum_required(VERSION 3.15)

project(SpreadSheet)

set(CMAKE_CXX_STANDARD 20)

include_directories(SpreadSheetHdrs)

add_executable(SpreadSheet 
    SpreadSheetSrc/main.cpp 
    SpreadSheetSrc/cell.cpp 
    SpreadSheetSrc/spread_sheet.cpp
)