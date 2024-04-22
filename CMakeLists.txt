cmake_minimum_required(VERSION 3.29)

project(PropX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(ext)
add_subdirectory(test)