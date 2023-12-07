find_package(GTest REQUIRED)

add_executable(string_test main.cpp)


target_link_libraries(string_test
 PRIVATE
  GTest::GTest
  string)

target_include_directories(string_test 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/lib/base)

add_test(string_gtest string_test)
