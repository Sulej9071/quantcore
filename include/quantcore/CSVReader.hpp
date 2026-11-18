
#pragma once

#include "quantcore/MarketBar.hpp"

#include <string>
#include <vector>

namespace quantcore {

class CSVReader {
public:
    static std::vector<MarketBar> read(
        const std::string& filename
    );
};

} // namespace quantcore
