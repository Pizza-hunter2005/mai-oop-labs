cmake_minimum_required(VERSION 3.12)
project(BalagurFate3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")


set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

# Подключение Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(tests tests/test.cpp)
target_link_libraries(tests PRIVATE gtest gtest_main)
# Установка стандартов и отладочных опций для тестов
target_compile_features(tests PRIVATE cxx_std_20)
target_compile_options(tests PRIVATE -g -O0)

add_test(NAME tests COMMAND tests)
