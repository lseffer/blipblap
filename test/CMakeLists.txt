cmake_minimum_required(VERSION 3.10)

set(sources "char_stream_test.cpp" "token_stream_test.cpp")

add_executable(unit_tests ${sources})

target_link_libraries(unit_tests libistream Catch2::Catch2WithMain)

set_target_properties(unit_tests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
