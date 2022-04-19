cmake_minimum_required(VERSION 3.22)
project(sherlock)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

if (WIN32)
    set("RE2C_EXECUTABLE" "E:\\re2c-3.0\\.build\\re2c.exe")
endif()

if (UNIX AND NOT APPLE)
    set("RE2C_EXECUTABLE" "/home/aryaman9199/re2c-3.0/.build/re2c")
endif()

set("RE2C_VERSION" 3.0)

find_package(RE2C REQUIRED)

RE2C_TARGET(NAME preprocessor INPUT ${PROJECT_SOURCE_DIR}/preprocessor.re OUTPUT preprocessor.cpp OPTIONS "-i")
RE2C_TARGET(NAME lexer INPUT ${PROJECT_SOURCE_DIR}/lexer.re OUTPUT lexer.cpp OPTIONS "-i")

file(GLOB srcs
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/include/*.h"
        )

add_executable(sherlock ${srcs} preprocessor.cpp lexer.cpp)