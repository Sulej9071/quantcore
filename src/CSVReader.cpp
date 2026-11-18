
#include "quantcore/CSVReader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace quantcore {

std::vector<MarketBar> CSVReader::read(
    const std::string& filename
) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Cannot open file: " + filename
        );
    }

    std::vector<MarketBar> bars;
    std::string line;

    // Read and validate the header
    if (!std::getline(file, line)) {
        throw std::runtime_error("Empty CSV file");
    }

    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }

    if (line != "date,open,high,low,close,volume") {
        throw std::runtime_error("Invalid CSV header");
    }

    std::size_t lineNumber = 1;

    while (std::getline(file, line)) {
        ++lineNumber;

        if (line.empty() || line == "\r") {
            continue;
        }

        std::stringstream ss(line);
        std::vector<std::string> fields;
        std::string field;

        while (std::getline(ss, field, ',')) {
            fields.push_back(field);
        }

        if (fields.size() != 6) {
            throw std::runtime_error(
                "Invalid CSV row at line " +
                std::to_string(lineNumber)
            );
        }

        try {
            MarketBar bar{
                fields[0],
                std::stod(fields[1]),
                std::stod(fields[2]),
                std::stod(fields[3]),
                std::stod(fields[4]),
                std::stod(fields[5])
            };

            bars.push_back(bar);

        } catch (const std::invalid_argument&) {
            throw std::runtime_error(
                "Invalid numeric value at line " +
                std::to_string(lineNumber)
            );
        } catch (const std::out_of_range&) {
            throw std::runtime_error(
                "Numeric value out of range at line " +
                std::to_string(lineNumber)
            );
        }
    }

    if (file.bad()) {
        throw std::runtime_error(
            "Error reading file: " + filename
        );
    }

    return bars;
}

} // namespace quantcore
