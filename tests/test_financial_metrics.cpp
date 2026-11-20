
#include <gtest/gtest.h>

#include "quantcore/FinancialMetrics.hpp"

#include <cmath>
#include <stdexcept>
#include <vector>

TEST(FinancialMetricsTest, AnnualizedVolatility) {
    std::vector<double> returns = {
        -0.01, 0.0, 0.01
    };

    // Sample std dev = 0.01
    double expected = 0.01 * std::sqrt(252.0);

    EXPECT_NEAR(
        quantcore::annualizedVolatility(returns),
        expected,
        1e-10
    );
}

TEST(FinancialMetricsTest, CumulativeReturn) {
    std::vector<double> returns = {
        0.10, -0.10
    };

    // 1.10 * 0.90 - 1 = -0.01
    EXPECT_NEAR(
        quantcore::cumulativeReturn(returns),
        -0.01,
        1e-10
    );
}

TEST(FinancialMetricsTest, SharpeRatio) {
    std::vector<double> returns = {
        0.01, 0.02, 0.03
    };

    // Mean = 0.02, sample std dev = 0.01
    double expected = 2.0 * std::sqrt(252.0);

    EXPECT_NEAR(
        quantcore::sharpeRatio(returns),
        expected,
        1e-10
    );
}

TEST(FinancialMetricsTest, MaxDrawdown) {
    std::vector<double> nav = {
        100.0, 120.0, 90.0, 130.0
    };

    EXPECT_DOUBLE_EQ(
        quantcore::maxDrawdown(nav),
        -0.25
    );
}

TEST(FinancialMetricsTest, RejectsZeroVolatilitySharpe) {
    std::vector<double> returns = {
        0.01, 0.01, 0.01
    };

    EXPECT_THROW(
        quantcore::sharpeRatio(returns),
        std::invalid_argument
    );
}
