//
// Created by rs on 24.01.25.
//

#include "TournamentSelectionStrategy.h"

#include <iostream>

namespace NGroupingChallenge {
    TournamentSelectionStrategy::TournamentSelectionStrategy(std::mt19937& randomEngine, std::uniform_int_distribution<>& individualIDRange, AbstractEvaluator& evaluator, const int& candidates)
        : SelectionStrategy(randomEngine, individualIDRange, evaluator)
        , candidates(candidates)
    {}

    Individual* TournamentSelectionStrategy::select(const std::vector<Individual*>& population) {
        Individual* best = nullptr;
        double bestScore = std::numeric_limits<double>::max();

        for (int i = 0; i < candidates; ++i) {
            Individual* current = population[individualIDRange(randomEngine)];
            double currentScore = current->evaluate(evaluator);

            if (currentScore < bestScore) {
                best = current;
                bestScore = currentScore;
            }
        }
        //std::cout << bestScore << "\n";
        return best;
    }

    int TournamentSelectionStrategy::getCandidates() const {
        return candidates;
    }

    void TournamentSelectionStrategy::setCandidates(const int& candidates) {
        this->candidates = candidates;
    }
} // NGroupingChallenge