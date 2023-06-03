project(Test)

set(TEST_SOURCE Test.cpp)
add_executable(Test ${TEST_SOURCE})

target_link_libraries(Test PRIVATE RealEngine)
target_include_directories(Test PUBLIC ${CMAKE_SOURCE_DIR}/include)