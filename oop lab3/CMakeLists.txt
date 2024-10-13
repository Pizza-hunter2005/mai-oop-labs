cmake_minimum_required(VERSION 3.10)
project(cppfigures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${INCLUDE_DIR})
# Автоматический поиск всех .cpp файлов в папке src
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
# Создание библиотеки из исходников
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCES})
add_executable(main main.cpp)
target_link_libraries(main PRIVATE ${CMAKE_PROJECT_NAME}_lib)

# ===================== Google Test ===================== #

# Подключение GoogleTest через FetchContent
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/v1.15.2.tar.gz
)
# Скачать и сделать доступным GoogleTest
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(tests tests/test.cpp)
target_link_libraries(tests gtest gtest_main ${CMAKE_PROJECT_NAME}_lib)
add_test(NAME tests COMMAND tests)


