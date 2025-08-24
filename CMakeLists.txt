cmake_minimum_required(VERSION 3.16)

project(LZSS-Archiver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

add_library(lzss STATIC project/lzss.cpp)
target_include_directories(lzss PUBLIC project)

add_executable(LZSS-Archiver project/main.cpp)
target_link_libraries(LZSS-Archiver PRIVATE lzss)

enable_testing()
add_subdirectory(tests)