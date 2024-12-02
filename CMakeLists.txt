cmake_minimum_required(VERSION 3.31.1)

project(AOC2024)

include (CTest)

set(CMAKE_CXX_COMPILER /opt/homebrew/Cellar/gcc/14.2.0_1/bin/g++-14)
#set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS_DEBUG)
set(CMAKE_CXX_FLAGS_RELEASE)

include_directories(./include)
include_directories(~/include)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(main src/main.cpp src/day1.cpp)
add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
    COMMENT "Transferring compile_commands.json..."
)

target_link_libraries(main PRIVATE ${LINK_LIBS})
