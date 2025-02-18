cmake_minimum_required(VERSION 3.10)
project(PBM LANGUAGES C VERSION 1.0.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()


if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()


# My variable
set (TEST "test.c")

set(
    SOURCES
    "src/BigInt/create.c"
    "src/BigInt/readings.c"
    "src/BigInt/to_string.c"
    "src/tools/base.c"
    "src/nums.c"
    TEST
)
set (
    INCLUDES
    "include/pbm_types.h"
    "include/pbm_BigInt.h"
    "include/pbm_nums.h"
    "include/tools/base.h"
)
set (
    INCLUDE_DIRECTORIES
    "include"
    "include/tools"
)

# add_library(${PROJECT_NAME} SHARED ${SOURCES} ${INCLUDES})
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTORIES})