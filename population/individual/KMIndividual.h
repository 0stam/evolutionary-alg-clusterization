//
// Created by rs on 27.01.25.
//

#ifndef KMINDIVIDUAL_H
#define KMINDIVIDUAL_H
#include "SinglePointCrossingIndividual.h"

namespace NGroupingChallenge {

class KMIndividual : public SinglePointCrossingIndividual{
public:
    KMIndividual(int numberOfPoints, int tournamentCount, std::mt19937& randomEngine, std::uniform_int_distribution<>& groupRange, std::uniform_int_distribution<>& pointIdxRange, AbstractEvaluator& evaluator);

    Individual* copy() const override;
};

} // NGroupingChallenge

#endif //KMINDIVIDUAL_H
