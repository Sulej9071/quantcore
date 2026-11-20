
#pragma once

#include "quantcore/strategy/Strategy.hpp"

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace quantcore {

class SMACrossoverStrategy : public Strategy {
public:
    SMACrossoverStrategy(
        std::string symbol,
        std::size_t fastWindow,
        std::size_t slowWindow
    );

    std::string name() const override;

    std::vector<TargetWeight> onMarket(
        const MarketSnapshot& market
    ) override;

    void reset() override;

private:
    std::string symbol_;
    std::size_t fastWindow_;
    std::size_t slowWindow_;

    std::vector<double> prices_;

    // No regime is known until enough data arrives
    std::optional<bool> previousBullish_;
};

} // namespace quantcore
