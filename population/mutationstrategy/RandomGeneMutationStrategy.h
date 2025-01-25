#ifndef RANDOMGENEMUTATIONSTRATEGY_H
#define RANDOMGENEMUTATIONSTRATEGY_H
#include <random>

#include "MutationStrategy.h"

namespace NGroupingChallenge {

class RandomGeneMutationStrategy : public MutationStrategy {
public:
    RandomGeneMutationStrategy(std::mt19937& randomEngine, std::uniform_int_distribution<>& groupRange, std::uniform_int_distribution<>& pointIdxRange);

    std::vector<int> mutate(std::vector<int> genes) override;
    std::string test() override;

private:
    std::mt19937& randomEngine;

    std::uniform_int_distribution<>& groupRange;
    std::uniform_int_distribution<>& pointIdxRange;
};

} // NGroupingChallenge

#endif //RANDOMGENEMUTATIONSTRATEGY_H
