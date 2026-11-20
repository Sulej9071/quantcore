
#include <gtest/gtest.h>

#include "quantcore/Returns.hpp"

#include <cmath>
#include <vector>

TEST(ReturnsTest, CalculatesSimpleReturns) {
    std::vector<double> prices = {
        100.0, 105.0, 102.0
    };

    auto returns = quantcore::simpleReturns(prices);

    ASSERT_EQ(returns.size(), 2u);

    EXPECT_NEAR(returns[0], 0.05, 1e-10);
    EXPECT_NEAR(returns[1], -3.0 / 105.0, 1e-10);
}

TEST(ReturnsTest, CalculatesLogReturns) {
    std::vector<double> prices = {
        100.0, 105.0
    };

    auto returns = quantcore::logReturns(prices);

    ASSERT_EQ(returns.size(), 1u);

    EXPECT_NEAR(
        returns[0],
        std::log(1.05),
        1e-10
    );
}

TEST(ReturnsTest, SinglePriceHasNoReturns) {
    std::vector<double> prices = {100.0};

    auto returns = quantcore::simpleReturns(prices);

    EXPECT_TRUE(returns.empty());
}
