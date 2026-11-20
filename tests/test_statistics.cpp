
#include <gtest/gtest.h>

#include "quantcore/Statistics.hpp"

#include <stdexcept>
#include <vector>

TEST(StatisticsTest, CalculatesMean) {
    std::vector<double> values = {2.0, 4.0, 6.0};

    auto stats = quantcore::calculateStatistics(values);

    EXPECT_DOUBLE_EQ(stats.mean, 4.0);
}

TEST(StatisticsTest, CalculatesMinAndMax) {
    std::vector<double> values = {-5.0, 2.0, 10.0, 3.0};

    auto stats = quantcore::calculateStatistics(values);

    EXPECT_DOUBLE_EQ(stats.min, -5.0);
    EXPECT_DOUBLE_EQ(stats.max, 10.0);
}

TEST(StatisticsTest, CalculatesSampleStdDev) {
    std::vector<double> values = {2.0, 4.0, 6.0};

    auto stats = quantcore::calculateStatistics(values);

    EXPECT_DOUBLE_EQ(stats.std_dev, 2.0);
}

TEST(StatisticsTest, RejectsEmptyVector) {
    std::vector<double> values;

    EXPECT_THROW(
        quantcore::calculateStatistics(values),
        std::invalid_argument
    );
}
