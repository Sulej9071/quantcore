
#pragma once

#include <vector>

namespace quantcore {

std::vector<double> simpleReturns(
    const std::vector<double>& prices
);

std::vector<double> logReturns(
    const std::vector<double>& prices
);

}
