cmake_minimum_required(VERSION 3.10)


set(
    SOURCES
    "./test.c"
)


add_executable(pbm_tests ${SOURCES})
target_link_libraries(pbm_tests PRIVATE PBM)
target_include_directories(pbm_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

# for correct run library
set_target_properties(pbm_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)