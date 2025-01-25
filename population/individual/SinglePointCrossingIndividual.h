#ifndef SINGLEPOINTCROSSINGINDIVIDUAL_H
#define SINGLEPOINTCROSSINGINDIVIDUAL_H
#include "Individual.h"

namespace NGroupingChallenge {

class SinglePointCrossingIndividual : public Individual {
public:
    SinglePointCrossingIndividual(int numberOfPoints, std::mt19937& randomEngine, std::uniform_int_distribution<>& groupRange);

    Individual* copy() const override;

    std::pair<Individual*, Individual*> cross(const Individual& other, std::mt19937& randomEngine, std::uniform_int_distribution<>& crossAtRange) const override;
};

} // NGroupingChallenge

#endif //SINGLEPOINTCROSSINGINDIVIDUAL_H
