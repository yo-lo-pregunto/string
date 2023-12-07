cmake_minimum_required(VERSION 3.26)

project(String VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)

enable_testing()

add_subdirectory(lib)
add_subdirectory(tests)
