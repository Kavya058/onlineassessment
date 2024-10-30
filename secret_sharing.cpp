#include <iostream>
#include <fstream>
#include <json.hpp>
#include <vector>
#include <cmath>
#include <string>

using json = nlohmann::json;

// Function to convert a value from a given base to decimal
long long decodeValue(const std::string& value, int base) {
    long long result = 0;
    for (char digit : value) {
        result *= base;
        if (isdigit(digit)) {
            result += digit - '0';
        } else {
            result += digit - 'a' + 10;
        }
    }
    return result;
}

// Function to compute the constant term of the polynomial using Lagrange interpolation
long long findConstantTerm(const std::vector<std::pair<int, long long>>& points, int k) {
    long long c = 0;
    for (int i = 0; i < k; ++i) {
        long long xi = points[i].first;
        long long yi = points[i].second;
        long long term = yi;
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                term *= (0 - points[j].first);
                term /= (xi - points[j].first); // Directly use division for simplicity
            }
        }
        c += term;
    }
    return c;
}

int main() {
    std::ifstream inputFile("input.json");
    json inputData;
    inputFile >> inputData;

    // Loop through each test case
    for (const auto& testCase : inputData["test_cases"]) {
        int n = testCase["keys"]["n"];
        int k = testCase["keys"]["k"];
        std::vector<std::pair<int, long long>> points;

        // Decode the y-values
        for (const auto& point : testCase["points"].items()) {
            int x = std::stoi(point.key());
            int base = std::stoi(point.value()["base"].get<std::string>());
            std::string valueStr = point.value()["value"];
            long long decodedValue = decodeValue(valueStr, base);
            points.emplace_back(x, decodedValue);
        }

        // Calculate the constant term c
        long long secretC = findConstantTerm(points, k);
        std::cout << "The constant term (secret) c for test case is: " << secretC << std::endl;
    }

    return 0;
}
