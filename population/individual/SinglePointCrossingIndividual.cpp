//
// Created by rs on 24.01.25.
//

#include "SinglePointCrossingIndividual.h"

#include <algorithm>

namespace NGroupingChallenge {
    SinglePointCrossingIndividual::SinglePointCrossingIndividual(int numberOfPoints, std::mt19937& randomEngine, std::uniform_int_distribution<>& groupRange)
        : Individual(numberOfPoints, randomEngine, groupRange)
    {}

    Individual* SinglePointCrossingIndividual::copy() const {
        return new SinglePointCrossingIndividual(*this);
    }

    std::pair<Individual*, Individual*> SinglePointCrossingIndividual::cross(const Individual& other, std::mt19937& randomEngine, std::uniform_int_distribution<>& crossAtRange) const {
        // TODO: it can be optimized a lot when genes are public
        // New individuals
        Individual* first = this->copy();
        Individual* second = other.copy();

        auto& thisGenes = genes;
        auto& otherGenes = other.getGenes();
        auto& firstGenes = *new vector<int>(thisGenes);
        auto& secondGenes = *new vector<int>(otherGenes);

        int crossIdx = crossAtRange(randomEngine);

        std::copy(thisGenes.begin() + crossIdx, thisGenes.end(), secondGenes.begin() + crossIdx);
        std::copy(otherGenes.begin() + crossIdx, otherGenes.end(), firstGenes.begin() + crossIdx);

        first->setGenes(firstGenes);
        second->setGenes(secondGenes);

        return {first, second};
    }
} // NGroupingChallenge