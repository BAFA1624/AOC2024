cmake_minimum_required(VERSION 3.31.1)

project(AOC2024)

include (CTest)

set(CMAKE_CXX_COMPILER /opt/homebrew/Cellar/gcc/14.2.0_1/bin/g++-14)
#set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -pedantic -O0 -ggdb -Wconversion -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -pedantic -O3 -ggdb -Wconversion")

include_directories(./include)
include_directories(~/include)

add_subdirectory(src)
add_subdirectory(tests)
