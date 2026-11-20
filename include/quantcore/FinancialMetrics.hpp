
#pragma once

#include <vector>

namespace quantcore {

double annualizedVolatility(
    const std::vector<double>& dailyReturns,
    double tradingDays = 252.0
);

double cumulativeReturn(
    const std::vector<double>& returns
);

double sharpeRatio(
    const std::vector<double>& dailyReturns,
    double annualRiskFreeRate = 0.0,
    double tradingDays = 252.0
);

double maxDrawdown(
    const std::vector<double>& portfolioValues
);

} // namespace quantcore
