cmake_minimum_required(VERSION 3.8)

project(market VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
