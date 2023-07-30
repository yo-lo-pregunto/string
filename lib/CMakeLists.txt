add_library(string SHARED string.c
    ${CMAKE_CURRENT_LIST_DIR}/include/string.h
    ${CMAKE_CURRENT_LIST_DIR}/base/base.h
    ${CMAKE_CURRENT_LIST_DIR}/slice/slice.c
    ${CMAKE_CURRENT_LIST_DIR}/slice/slice.h)

target_include_directories(string 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/slice
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/base)
