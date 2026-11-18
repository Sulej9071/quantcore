#pragma once

#include <vector>

namespace quantcore {

struct Statistics {
    double min;
    double max;
    double mean;
    double std_dev;
};

Statistics calculateStatistics(
    const std::vector<double>& values
);

}