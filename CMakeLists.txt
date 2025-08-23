cmake_minimum_required(VERSION 3.16)

project(LZSS-Archiver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LZSS-Archiver
    project/main.cpp
    project/lzss.cpp
)

target_include_directories(LZSS-Archiver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/project)