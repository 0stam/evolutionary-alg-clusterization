#ifndef CPOINTLOADER_H
#define CPOINTLOADER_H

#include <vector>
#include <string>

#include "../../Point.h"

namespace NGroupingChallenge {
    class CPointLoader {
    public:
        static std::vector<CPoint> vLoadPointsFromCSV(const std::string& sFilePath);
    };
}

#endif // CPOINTLOADER_H