
cmake_minimum_required(VERSION 3.20)

project(QuantCore VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -----------------------------------
# QuantCore library
# -----------------------------------

add_library(quantcore
    src/CSVReader.cpp
    src/MovingAverage.cpp
    src/Statistics.cpp
    src/Returns.cpp
    src/FinancialMetrics.cpp
    src/strategy/SMACrossoverStrategy.cpp
)

target_include_directories(quantcore
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(quantcore PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# -----------------------------------
# QuantCore CLI
# -----------------------------------

add_executable(quantcore_cli
    src/main.cpp
)

target_link_libraries(quantcore_cli
    PRIVATE quantcore
)

# -----------------------------------
# Unit tests
# -----------------------------------

enable_testing()

find_package(GTest REQUIRED)

add_executable(quantcore_tests
    tests/test_statistics.cpp
    tests/test_moving_average.cpp
    tests/test_returns.cpp
    tests/test_financial_metrics.cpp
    tests/test_sma_strategy.cpp
)

target_link_libraries(quantcore_tests
    PRIVATE
        quantcore
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(quantcore_tests)
