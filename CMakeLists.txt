cmake_minimum_required(VERSION 3.6...3.15)

project(nano-cereal LANGUAGES CXX VERSION 1.3.0)

add_executable(main example/main.cpp)
target_include_directories(main PUBLIC include)
