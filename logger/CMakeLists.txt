cmake_minimum_required(VERSION 3.8)
project(logger VERSION 1.0)

add_library(logger INTERFACE)

target_include_directories(logger INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(logger INTERFACE cxx_std_20)
