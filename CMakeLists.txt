
cmake_minimum_required(VERSION 3.20)

project(QuantCore VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Our reusable C++ library
add_library(quantcore
    src/CSVReader.cpp
    src/MovingAverage.cpp
)

target_include_directories(quantcore
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(quantcore PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Command-line application
add_executable(quantcore_cli
    src/main.cpp
)

target_link_libraries(quantcore_cli
    PRIVATE quantcore
)
