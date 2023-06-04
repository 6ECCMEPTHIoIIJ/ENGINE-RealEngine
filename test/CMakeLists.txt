project(Tests)

set(TEST_SOURCE Test.cpp)
add_executable(Tests ${TEST_SOURCE})

target_link_libraries(Tests PRIVATE RealEngine)
target_include_directories(Tests PUBLIC ${CMAKE_SOURCE_DIR}/include)