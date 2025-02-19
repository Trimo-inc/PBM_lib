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
set(
    SOURCES
    "src/BigInt/create.c"
    "src/BigInt/readings.c"
    "src/BigInt/to_string.c"
    "src/tools/base.c"
    "src/nums.c"
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

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTORIES})



# ON if tests
option(PBM_BUILD_TESTS "Build PBM tests" ON)
if(PBM_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()