cmake_minimum_required(VERSION 3.0.0)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

project(runTests)

add_executable(runTests tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

