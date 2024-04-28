cmake_minimum_required(VERSION 3.28)

project(PropX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate documentation
find_package(Doxygen REQUIRED)
doxygen_add_docs(${PROJECT_NAME}Documentation 
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doc 
    CONFIG_FILE ${CMAKE_SOURCE_DIR}/doc/Doxyfile
)

# set(ENV{PGPASSFILE} "${CMAKE_SOURCE_DIR}/.pgpass")

enable_testing()

add_subdirectory(ext)
add_subdirectory(src)
add_subdirectory(test)