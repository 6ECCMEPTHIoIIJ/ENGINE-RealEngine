cmake_minimum_required(VERSION 3.25)

project(RealEngine)

SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
        )

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
        )

SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/lib
        CACHE PATH
        "Single Directory for all"
        )

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_link_options(-static)

add_subdirectory(include)
add_subdirectory(external)
add_subdirectory(sources)
add_subdirectory(test)

set(REAL_ENGINE_SOURCES RealEngine.cpp)
add_library(RealEngine ${REAL_ENGINE_SOURCES})

target_include_directories(RealEngine PUBLIC ${CMAKE_SOURCE_DIR}/include)