include_directories(../include)

add_executable(test1 day_1_input.cpp ../src/day1/day1.cpp)
add_test(
    NAME test1 COMMAND test1
)
