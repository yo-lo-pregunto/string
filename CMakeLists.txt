cmake_minimum_required(VERSION 3.26)

project(String)

add_subdirectory(src/string)

add_executable(String ./test/main.c)

target_link_libraries(${PROJECT_NAME} string)
