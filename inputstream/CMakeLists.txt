cmake_minimum_required(VERSION 3.10)

set(sources "src/token_stream.cpp" "src/char_stream.cpp")

add_library(libistream)

target_sources(libistream
    PRIVATE
    ${sources}
)

target_include_directories(libistream
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/inputstream
)
