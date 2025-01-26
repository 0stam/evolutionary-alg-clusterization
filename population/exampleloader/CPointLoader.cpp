#include "CPointLoader.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

namespace NGroupingChallenge {
    std::vector<CPoint> CPointLoader::vLoadPointsFromCSV(const std::string& sFilePath) {
        std::vector<CPoint> vPoints;
        std::ifstream file(sFilePath);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << sFilePath << std::endl;
            return vPoints;
        }

        std::cout << "Loading points from CSV file: " << sFilePath << std::endl;

        while (std::getline(file, line)) {
            CPoint point;
            std::stringstream ss(line);
            std::string value;
            while (std::getline(ss, value, ',')) {
                point.vAddCoordinate(std::stod(value));
            }
            vPoints.push_back(point);
        }

        std::cout << "Finished loading points. Total points loaded: " << vPoints.size() << std::endl;

        return vPoints;
    }
}