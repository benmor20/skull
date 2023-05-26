# General setup
cmake_minimum_required(VERSION 3.22)
project(skull
        VERSION 1.0
        LANGUAGES C
)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_CLANG_TIDY "clang-tidy")

# Main code
add_subdirectory(src)

# Test code
include(CTest)
find_library(CRITERION criterion REQUIRED)
set(CRITERION_FLAGS --verbose -j1)
add_subdirectory(test)
