cmake_minimum_required(VERSION 3.10)

project(blipblap VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(inputstream)
add_subdirectory(test)
add_subdirectory(external/Catch2)

set(sources "src/main.cpp")
add_executable(blipblap ${sources})

target_link_libraries(blipblap libistream)

set_target_properties(blipblap
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
