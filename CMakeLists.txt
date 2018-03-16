cmake_minimum_required(VERSION 3.0)

project(DateTimeGrammars)

option(BUILD_TESTS "Set ON to build unit tests" OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_library(DateTimeGrammars INTERFACE)
target_include_directories(DateTimeGrammars INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt5 REQUIRED COMPONENTS Core)
include_directories(${Qt5Core_INCLUDE_DIRS})

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.60 REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
