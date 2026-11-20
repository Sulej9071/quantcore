
#pragma once

#include "quantcore/MarketBar.hpp"

#include <string>
#include <vector>

namespace quantcore {

// Market data for one security
struct InstrumentBar {
    std::string symbol;
    MarketBar bar;
};

// All available observations at one timestamp
struct MarketSnapshot {
    std::string date;
    std::vector<InstrumentBar> instruments;
};

// Requested allocation for one security
struct TargetWeight {
    std::string symbol;
    double weight;
};

// Universal interface for all strategies
class Strategy {
public:
    virtual ~Strategy() = default;

    virtual std::string name() const = 0;

    virtual std::vector<TargetWeight> onMarket(
        const MarketSnapshot& market
    ) = 0;

    virtual void reset() = 0;
};

} // namespace quantcore
