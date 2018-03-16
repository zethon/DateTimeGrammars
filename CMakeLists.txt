cmake_minimum_required(VERSION 3.0)

project(DateTimeGrammars)

option(BUILD_TESTS "Set ON to build unit tests" OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MACOSX_RPATH 1)

add_library(DateTimeGrammars INTERFACE)
target_include_directories(DateTimeGrammars INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set(Boost_USE_STATIC_LIBS ON)
# set(Boost_USE_MULTITHREADED ON)
# set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.60 REQUIRED COMPONENTS thread unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# # define testing
# enable_testing()
# add_test (${projectname}_test ${CMAKE_BINARY_DIR}/${projectname}_test)

# dependencies
# add_custom_target (build-test COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${CMAKE_BINARY_DIR}/${projectname}_test)
# add_dependencies(${projectname}_test ${projectname})