
#pragma once

#include <cstddef>
#include <vector>

namespace quantcore {

double simpleMovingAverage(
    const std::vector<double>& prices,
    std::size_t window
);

} // namespace quantcore
