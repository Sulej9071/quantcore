
#pragma once

#include <string>

namespace quantcore {

struct MarketBar {
    std::string date;
    double open;
    double high;
    double low;
    double close;
    double volume;
};

} // namespace quantcore
