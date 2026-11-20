
#include "quantcore/strategy/SMACrossoverStrategy.hpp"
#include "quantcore/MovingAverage.hpp"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace quantcore {

SMACrossoverStrategy::SMACrossoverStrategy(
    std::string symbol,
    std::size_t fastWindow,
    std::size_t slowWindow
)
    : symbol_(std::move(symbol)),
      fastWindow_(fastWindow),
      slowWindow_(slowWindow)
{
    if (symbol_.empty()) {
        throw std::invalid_argument(
            "Symbol cannot be empty"
        );
    }

    if (fastWindow_ == 0 ||
        fastWindow_ >= slowWindow_) {
        throw std::invalid_argument(
            "Require 0 < fastWindow < slowWindow"
        );
    }
}

std::string SMACrossoverStrategy::name() const {
    return "SMA Crossover";
}

std::vector<TargetWeight>
SMACrossoverStrategy::onMarket(
    const MarketSnapshot& market
) {
    // Find the security this strategy follows.
    for (const auto& instrument : market.instruments) {

        if (instrument.symbol != symbol_) {
            continue;
        }

        double close = instrument.bar.close;

        if (!std::isfinite(close) || close <= 0.0) {
            throw std::invalid_argument(
                "Close price must be finite and positive"
            );
        }

        prices_.push_back(close);

        // Warm-up period
        if (prices_.size() < slowWindow_) {
            return {};
        }

        double fastSMA = simpleMovingAverage(
            prices_, fastWindow_
        );

        double slowSMA = simpleMovingAverage(
            prices_, slowWindow_
        );

        bool bullish = fastSMA > slowSMA;

        // Generate a target on the first valid
        // observation or when the regime changes.
        if (!previousBullish_.has_value() ||
            bullish != *previousBullish_) {

            previousBullish_ = bullish;

            double target = bullish ? 1.0 : 0.0;

            return {{symbol_, target}};
        }

        return {};
    }

    // No bar for our instrument in this snapshot
    return {};
}

void SMACrossoverStrategy::reset() {
    prices_.clear();
    previousBullish_.reset();
}

} // namespace quantcore
