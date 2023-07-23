add_library(string SHARED string.c string.h)

target_include_directories(string PUBLIC ${CMAKE_CURRENT_LIST_DIR})
