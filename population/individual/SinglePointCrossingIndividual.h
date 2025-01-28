#ifndef SINGLEPOINTCROSSINGINDIVIDUAL_H
#define SINGLEPOINTCROSSINGINDIVIDUAL_H
#include "Individual.h"

namespace NGroupingChallenge {

class SinglePointCrossingIndividual : public Individual {
public:
    explicit SinglePointCrossingIndividual(int numberOfPoints);
    SinglePointCrossingIndividual(int numberOfPoints, std::mt19937& randomEngine, std::uniform_int_distribution<>& groupRange);

    Individual* copy() const override;

    std::pair<Individual*, Individual*> cross(Individual& other, std::mt19937& randomEngine, std::uniform_int_distribution<>& crossAtRange, AbstractEvaluator& evaluator) const override;
};

} // NGroupingChallenge

#endif //SINGLEPOINTCROSSINGINDIVIDUAL_H
