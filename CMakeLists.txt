cmake_minimum_required(VERSION 3.28)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(zstr CXX)

set(CMAKE_BUILD_TYPE Debug)

find_package(ZLIB REQUIRED)

add_library(zstr STATIC)
target_sources(
    zstr
    PUBLIC FILE_SET
           lib_zstr
           TYPE
           CXX_MODULES
           FILES
           mod.cppm)
target_compile_features(zstr PUBLIC cxx_std_20)
target_link_libraries(zstr PUBLIC ZLIB::ZLIB)
