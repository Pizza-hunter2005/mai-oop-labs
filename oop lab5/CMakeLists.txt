cmake_minimum_required(VERSION 3.12)
project(cppallocators)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")


set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

# ===================== Google Test ===================== #
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(tests tests/test01.cpp)

target_link_libraries(tests gtest gtest_main)

# Установка стандартов и отладочных опций для тестов
target_compile_features(tests PRIVATE cxx_std_20)
target_compile_options(tests PRIVATE -g -O0)

add_test(NAME tests COMMAND tests)
