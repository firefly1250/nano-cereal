cmake_minimum_required(VERSION 3.6)

project(nano-cereal LANGUAGES CXX VERSION 1.3.0)

set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-long-long -pedantic")


add_executable(main example/main.cpp)
target_include_directories(main PUBLIC include etl/include)

add_executable(test_input test/test_input.cpp)
target_include_directories(test_input PUBLIC include cereal/include etl/include)

add_executable(test_output test/test_output.cpp)
target_include_directories(test_output PUBLIC include cereal/include etl/include)