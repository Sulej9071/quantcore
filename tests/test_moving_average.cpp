
#include <gtest/gtest.h>

#include "quantcore/MovingAverage.hpp"

#include <stdexcept>
#include <vector>

TEST(MovingAverageTest, CalculatesCorrectly) {
    std::vector<double> prices = {
        100.0, 102.0, 104.0
    };

    EXPECT_DOUBLE_EQ(
        quantcore::simpleMovingAverage(prices, 2),
        103.0
    );
}

TEST(MovingAverageTest, WindowOneReturnsLastPrice) {
    std::vector<double> prices = {
        100.0, 102.0, 104.0
    };

    EXPECT_DOUBLE_EQ(
        quantcore::simpleMovingAverage(prices, 1),
        104.0
    );
}

TEST(MovingAverageTest, RejectsInvalidWindow) {
    std::vector<double> prices = {100.0, 102.0};

    EXPECT_THROW(
        quantcore::simpleMovingAverage(prices, 0),
        std::invalid_argument
    );

    EXPECT_THROW(
        quantcore::simpleMovingAverage(prices, 5),
        std::invalid_argument
    );
}
