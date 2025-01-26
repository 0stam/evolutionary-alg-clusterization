#ifndef CCLUSTERSAVER_H
#define CCLUSTERSAVER_H
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

namespace NGroupingChallenge {
    class CClusterSaver {
    public:
        static void vSaveClustersToCSV(const std::vector<int>& vClusters, const std::string& sFilePath) {
            // Check if the file exists, if not create it
            std::ifstream infile(sFilePath);
            if (!infile.good()) {
                std::ofstream createFile(sFilePath);
                createFile.close();
            }

            std::ofstream file(sFilePath);
            if (!file.is_open()) {
                std::cerr << "Error: Could not open file " << sFilePath << std::endl;
                return;
            }

            for (const int& cluster : vClusters) {
                file << cluster << std::endl;
            }

            file.close();
            std::cout << "Clusters saved to CSV file: " << sFilePath << std::endl;
        }
    };
};

#endif //CCLUSTERSAVER_H
