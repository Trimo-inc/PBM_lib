cmake_minimum_required(VERSION 3.10)
project(PBM LANGUAGES C VERSION 1.0.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

# 'x64' || 'Win32' 
set(CMAKE_GENERATOR_PLATFORM x64)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()



if(CMAKE_GENERATOR_PLATFORM STREQUAL "x64")
    message("ARCH is 64-bits")
    add_definitions(-DARCH=64)
elseif(CMAKE_GENERATOR_PLATFORM STREQUAL "x32")
    message("ARCH is 32-bits")
    add_definitions(-DARCH=32)
endif()



# My variable
set(
    SOURCES
    "src/BigInt/create.c"
    "src/BigInt/readings.c"
    "src/BigInt/to_string.c"
    "src/tools/base.c"
    "src/nums.c"

    "src/BigInteger/Natural/base.c"
    "src/BigInteger/Natural/create.c"
    "src/BigInteger/Natural/spec.c"
)
set (
    INCLUDES
    "include/pbm_types.h"
    "include/pbm_BigInt.h"
    "include/BigInteger/pbm_natural.h"
    "include/pbm_nums.h"
    "include/tools/base.h"
)
set (
    INCLUDE_DIRECTORIES
    "include/"
    "include/tools"
    "include/BigInteger"
)

include_directories(${INCLUDE_DIRECTORIES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTORIES})



# ON if tests
option(PBM_BUILD_TESTS "Build PBM tests" ON)
if(PBM_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()