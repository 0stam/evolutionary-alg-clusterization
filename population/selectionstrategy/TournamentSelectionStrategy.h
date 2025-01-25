#ifndef TOURNAMENTSELECTIONSTRATEGY_H
#define TOURNAMENTSELECTIONSTRATEGY_H
#include "SelectionStrategy.h"

namespace NGroupingChallenge {

class TournamentSelectionStrategy : public SelectionStrategy {
public:
    TournamentSelectionStrategy(std::mt19937& randomEngine, std::uniform_int_distribution<>& individualIDRange, AbstractEvaluator& evaluator, const int& candidates);

    Individual* select(const std::vector<Individual*>& population) override;

    int getCandidates() const;
    void setCandidates(const int& candidates);

private:
    int candidates;
};

} // NGroupingChallenge

#endif //TOURNAMENTSELECTIONSTRATEGY_H
