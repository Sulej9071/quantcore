
#include <gtest/gtest.h>

#include "quantcore/strategy/SMACrossoverStrategy.hpp"

#include <stdexcept>
#include <string>
#include <vector>

namespace {

quantcore::MarketSnapshot makeSnapshot(
    const std::string& date,
    double close
) {
    quantcore::MarketBar bar{
        date, close, close, close, close, 1000.0
    };

    return {date, {{"SAMPLE", bar}}};
}

} // namespace

TEST(SMAStrategyTest, RejectsInvalidWindows) {
    EXPECT_THROW(
        quantcore::SMACrossoverStrategy("SAMPLE", 0, 5),
        std::invalid_argument
    );

    EXPECT_THROW(
        quantcore::SMACrossoverStrategy("SAMPLE", 5, 3),
        std::invalid_argument
    );
}

TEST(SMAStrategyTest, WaitsForEnoughData) {
    quantcore::SMACrossoverStrategy strategy(
        "SAMPLE", 2, 3
    );

    EXPECT_TRUE(
        strategy.onMarket(makeSnapshot("Day1", 10)).empty()
    );

    EXPECT_TRUE(
        strategy.onMarket(makeSnapshot("Day2", 11)).empty()
    );
}

TEST(SMAStrategyTest, GeneratesLongTarget) {
    quantcore::SMACrossoverStrategy strategy(
        "SAMPLE", 2, 3
    );

    strategy.onMarket(makeSnapshot("Day1", 10));
    strategy.onMarket(makeSnapshot("Day2", 11));

    auto targets = strategy.onMarket(
        makeSnapshot("Day3", 12)
    );

    ASSERT_EQ(targets.size(), 1u);
    EXPECT_EQ(targets[0].symbol, "SAMPLE");
    EXPECT_DOUBLE_EQ(targets[0].weight, 1.0);
}

TEST(SMAStrategyTest, ExitsWhenTrendReverses) {
    quantcore::SMACrossoverStrategy strategy(
        "SAMPLE", 2, 3
    );

    strategy.onMarket(makeSnapshot("Day1", 10));
    strategy.onMarket(makeSnapshot("Day2", 11));
    strategy.onMarket(makeSnapshot("Day3", 12));

    // Still bullish: no new instruction
    auto unchanged = strategy.onMarket(
        makeSnapshot("Day4", 13)
    );
    EXPECT_TRUE(unchanged.empty());

    // Fast SMA falls below slow SMA
    auto targets = strategy.onMarket(
        makeSnapshot("Day5", 8)
    );

    ASSERT_EQ(targets.size(), 1u);
    EXPECT_DOUBLE_EQ(targets[0].weight, 0.0);
}

TEST(SMAStrategyTest, ResetClearsHistory) {
    quantcore::SMACrossoverStrategy strategy(
        "SAMPLE", 2, 3
    );

    strategy.onMarket(makeSnapshot("Day1", 10));
    strategy.onMarket(makeSnapshot("Day2", 11));
    strategy.onMarket(makeSnapshot("Day3", 12));

    strategy.reset();

    EXPECT_TRUE(
        strategy.onMarket(makeSnapshot("Day4", 20)).empty()
    );
}
