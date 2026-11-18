
#include "quantcore/Statistics.hpp"

#include <cmath>
#include <stdexcept>

namespace quantcore {

Statistics calculateStatistics(
    const std::vector<double>& values
) {
    if (values.size() < 2) {
        throw std::invalid_argument(
            "At least 2 observations are required"
        );
    }

    Statistics stats{};

    stats.min = values[0];
    stats.max = values[0];

    double sum = 0.0;
    double squared_deviations = 0.0;

    // First pass: min, max and mean
    for (double value : values) {

        if (value < stats.min) {
            stats.min = value;
        }

        if (value > stats.max) {
            stats.max = value;
        }

        sum += value;
    }

    stats.mean = sum / values.size();

    // Second pass: variance
    for (double value : values) {
        double diff = value - stats.mean;
        squared_deviations += diff * diff;
    }

    double sample_variance =
    squared_deviations / (values.size() - 1);

    stats.std_dev = std::sqrt(sample_variance);

    return stats;
}

} // namespace quantcore
