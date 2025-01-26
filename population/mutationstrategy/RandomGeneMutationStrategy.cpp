//
// Created by rs on 24.01.25.
//

#include "RandomGeneMutationStrategy.h"

#include <iostream>

namespace NGroupingChallenge {
    RandomGeneMutationStrategy::RandomGeneMutationStrategy(std::mt19937& randomEngine, std::uniform_int_distribution<>& groupRange, std::uniform_int_distribution<>& pointIdxRange)
        : randomEngine(randomEngine)
        , groupRange(groupRange)
        , pointIdxRange(pointIdxRange)
    {}

    std::vector<int> RandomGeneMutationStrategy::mutate(std::vector<int> genes) {
        genes[pointIdxRange(randomEngine)] = groupRange(randomEngine);

        return genes;
    }
} // NGroupingChallenge