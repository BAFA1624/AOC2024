include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

add_executable(day2 main.cpp day2.cpp)
add_custom_command(
    TARGET day2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/build/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
    COMMENT "Transferring compile_commands.json..."
)
