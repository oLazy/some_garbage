cmake_minimum_required(VERSION 3.12)
project(z1damt)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(z1damt_exe ${SOURCE_FILES})

include_directories(z1amt)

add_subdirectory(z1amt)
add_subdirectory(z1amt_test)

target_link_libraries(z1damt_exe z1amt)

