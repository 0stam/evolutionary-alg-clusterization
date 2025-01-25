//
// Created by rs on 24.01.25.
//

#include "SelectionStrategy.h"

namespace NGroupingChallenge {
    SelectionStrategy::SelectionStrategy(std::mt19937& randomEngine, std::uniform_int_distribution<>& individualIDRange, AbstractEvaluator& evaluator)
        : randomEngine(randomEngine)
        , individualIDRange(individualIDRange)
        , evaluator(evaluator)
    {}
} // NGroupingChallenge