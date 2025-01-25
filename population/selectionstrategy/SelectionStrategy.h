//
// Created by rs on 24.01.25.
//

#ifndef SELECTIONSTRATEGY_H
#define SELECTIONSTRATEGY_H
#include "../individual/Individual.h"

namespace NGroupingChallenge {

class SelectionStrategy {
public:
    SelectionStrategy(std::mt19937& randomEngine, std::uniform_int_distribution<>& individualIDRange, AbstractEvaluator& evaluator);
    virtual ~SelectionStrategy() = default;

    virtual Individual* select(const std::vector<Individual*>& population) = 0;

protected:
    std::mt19937& randomEngine;
    std::uniform_int_distribution<>& individualIDRange;

    AbstractEvaluator& evaluator;
};

} // NGroupingChallenge

#endif //SELECTIONSTRATEGY_H
