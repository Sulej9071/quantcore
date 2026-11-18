
#include "quantcore/Returns.hpp"

#include <cmath>
#include <stdexcept>

namespace quantcore {

std::vector<double> simpleReturns(
    const std::vector<double>& prices
) {
    std::vector<double> returns;

    if (prices.size() < 2) {
        return returns;
    }

    returns.reserve(prices.size() - 1);

    for (std::size_t i = 1; i < prices.size(); ++i) {

        // TODO:
        // 1. Read prices[i]
        // 2. Read prices[i - 1]
        // 3. Calculate simple return
        // 4. Append result to returns
        //
        // Hint: returns.push_back(...);

        double p_i = prices[i];
        double p_i_1 = prices[i-1];

        returns.push_back((p_i/p_i_1)-1);

    }

    return returns;
}

std::vector<double> logReturns(
    const std::vector<double>& prices
) {
    std::vector<double> returns;

    if (prices.size() < 2) {
        return returns;
    }

    returns.reserve(prices.size() - 1);

    for (std::size_t i = 1; i < prices.size(); ++i) {

        // TODO:
        // Use std::log() from <cmath>

        double p_i = prices[i];
        double p_i_1 = prices[i-1];

        returns.push_back(std::log(p_i/p_i_1));
    }

    return returns;
}

}
