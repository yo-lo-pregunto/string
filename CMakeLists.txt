cmake_minimum_required(VERSION 3.26)

project(String VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)

add_subdirectory(lib)

add_executable(String ./test/main.c)

target_link_libraries(${PROJECT_NAME} string)
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/lib/base)
