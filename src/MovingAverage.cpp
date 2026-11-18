#include "quantcore/MovingAverage.hpp"

#include <numeric>
#include <stdexcept>

namespace quantcore {

double simpleMovingAverage(
    const std::vector<double>& prices,
    std::size_t window
) {
    if (window == 0 || window > prices.size()) {
        throw std::invalid_argument(
            "Invalid moving average window"
        );
    }

    auto start = prices.end() - window;

    double sum = std::accumulate(
        start,
        prices.end(),
        0.0
    );

    return sum / static_cast<double>(window);
}

} // namespace quantcore
