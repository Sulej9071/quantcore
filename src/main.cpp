
#include "quantcore/CSVReader.hpp"
#include "quantcore/MovingAverage.hpp"

#include <exception>
#include <iostream>
#include <vector>
#include <stdexcept>

int main() {
    try {
        // 1. Read historical market data
        auto bars = quantcore::CSVReader::read(
            "data/sample_prices.csv"
        );

        if (bars.empty()) {
            throw std::runtime_error(
                "No market data available"
            );
        }

        // 2. Extract closing prices
        std::vector<double> closes;
        closes.reserve(bars.size());

        for (const auto& bar : bars) {
            closes.push_back(bar.close);
        }

        // 3. Calculate moving average
        constexpr std::size_t window = 5;

        double sma = quantcore::simpleMovingAverage(
            closes, window
        );

        // 4. Display results
        std::cout << "========================\n";
        std::cout << "    QuantCore v0.1\n";
        std::cout << "========================\n";

        std::cout << "Observations: "
                  << bars.size() << '\n';

        std::cout << "Last date: "
                  << bars.back().date << '\n';

        std::cout << "Last close: "
                  << closes.back() << '\n';

        std::cout << "SMA(" << window << "): "
                  << sma << '\n';

    } catch (const std::exception& e) {
        std::cerr << "Error: "
                  << e.what() << '\n';

        return 1;
    }

    return 0;
}
