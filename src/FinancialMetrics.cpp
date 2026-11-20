
#include "quantcore/FinancialMetrics.hpp"
#include "quantcore/Statistics.hpp"

#include <cmath>
#include <stdexcept>

namespace quantcore {

double annualizedVolatility(
    const std::vector<double>& dailyReturns,
    double tradingDays
) {
    // TODO:
    // 1. Validate tradingDays > 0
    if (!std::isfinite(tradingDays) || tradingDays <= 0.0) {
        throw std::invalid_argument(
            "Trading days must be finite and positive"
        );
    }
    // 2. Calculate statistics of dailyReturns
    auto stats = calculateStatistics(dailyReturns);

    // 4. Annualize it using sqrt(tradingDays)
    return stats.std_dev * std::sqrt(tradingDays);
}

double cumulativeReturn(
    const std::vector<double>& returns
) {
    if (returns.empty()) {
        throw std::invalid_argument(
            "Returns should have at leat one value"
        );
    }
    // TODO:
    // 1. Initialize wealth = 1.0
    double wealth = 1.0;
    // 2. Loop through daily returns
    for (double value : returns) {

        if (!std::isfinite(value) || value < -1.0) {
            throw std::invalid_argument(
                "Invalid return value"
            );
        }

        wealth *= (1.0 + value);
    }
    
    // 4. Return wealth - 1.0

    return wealth - 1;
}

double sharpeRatio(
    const std::vector<double>& dailyReturns,
    double annualRiskFreeRate,
    double tradingDays
) {
    // TODO:
    // 1. Validate inputs
    if (tradingDays <= 0) {
        throw std::invalid_argument(
            "Trading days should be superior to 0"
        );
    }
    if (dailyReturns.empty()) {
        throw std::invalid_argument(
            "Returns should have at leat one value"
        );
    }
    if (!std::isfinite(annualRiskFreeRate) || annualRiskFreeRate <= -1.0) {
        throw std::invalid_argument(
            "Risk free rate not usable"
        );
    }
    // 2. Calculate daily mean and sample std dev
    auto stats = calculateStatistics(dailyReturns);

    double mean_return = stats.mean;
    double std_dev = stats.std_dev;

    // 3. Convert annual risk-free rate to a daily rate
    double dailyRiskFreeRate = std::pow(1.0 + annualRiskFreeRate, 1.0 / tradingDays) - 1.0;

    // 4. Calculate annualized Sharpe ratio
    if (std_dev == 0) {
        throw std::invalid_argument(
            "Volatility equals 0, no calculation possible"
        );
    }

    return ((mean_return - dailyRiskFreeRate)/std_dev) * std::sqrt(tradingDays);
}

double maxDrawdown(
    const std::vector<double>& portfolioValues
) {
    // TODO:
    // 1. Validate portfolioValues is not empty
    if (portfolioValues.empty()) {
        throw std::invalid_argument(
            "portfolioValues should have at leat one value"
        );
    }
    // 2. Initialize peak with first NAV
    double peak = portfolioValues[0];
    double worstDrawdown = 0.0;

    // 3. Loop through NAV values
    for (double nav : portfolioValues) {

        if (!std::isfinite(nav) || nav <= 0.0) {
            throw std::invalid_argument(
                "Portfolio NAV must be finite and positive"
            );
        }
        
        // 4. Update running peak
        if (nav > peak) {
            peak = nav;
        }

        // 5. Calculate drawdown relative to peak
        double dd = nav/peak - 1; 

        // 6. Keep the worst drawdown
        if (dd < worstDrawdown) {
            worstDrawdown = dd;
        }
    }

    return worstDrawdown;
}

} // namespace quantcore
