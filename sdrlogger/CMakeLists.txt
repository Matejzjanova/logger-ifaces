cmake_minimum_required(VERSION 3.8)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

project(sdrlogger)
add_library(sdrlogger include/sdrlogger/sdrlogger.h src/sdrlogger.cpp)
target_link_libraries(sdrlogger PUBLIC logger)

target_include_directories(sdrlogger PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_executable(sdrlogger_test test/test.cpp)
target_link_libraries(sdrlogger PUBLIC logger)
target_link_libraries(sdrlogger_test PUBLIC sdrlogger)
target_link_libraries(sdrlogger_test PRIVATE
        GTest::gtest GTest::gmock GTest::gtest_main )

add_test(NAME sdrlogger_test COMMAND sdrlogger_test)
