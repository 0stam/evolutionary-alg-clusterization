//
// Created by rs on 27.01.25.
//

#include "KMIndividual.h"

namespace NGroupingChallenge {
    KMIndividual::KMIndividual(int numberOfPoints, int tournamentCount, std::mt19937& randomEngine, std::uniform_int_distribution<>& groupRange, std::uniform_int_distribution<>& pointIdxRange, AbstractEvaluator& evaluator)
        : SinglePointCrossingIndividual(numberOfPoints)
    {
        int numberOfGroups = groupRange.max();
        int centers[numberOfGroups];

        centers[0] = pointIdxRange(randomEngine);

        for (int i = 1; i < numberOfGroups; ++i) {
            //centers[i] = pointIdxRange(randomEngine);
            double maxDistance = 0;

            for (int j = 0; j < tournamentCount; ++j) {
                int idx = pointIdxRange(randomEngine);
                double distance = 0;

                for (int k = 0; k < i; ++k) {
                    distance += evaluator.distanceBetween(idx, centers[k]);
                }

                if (distance > maxDistance) {
                    maxDistance = distance;
                    centers[i] = idx;
                }
            }
        }

        for (int i = 0; i < numberOfPoints; ++i) {
            double minDistance = evaluator.distanceBetween(i, centers[0]);
            genes[i] = 1;

            for (int j = 1; j < numberOfGroups; ++j) {
                double distance = evaluator.distanceBetween(i, centers[j]);

                if (distance < minDistance) {
                    minDistance = distance;
                    genes[i] = j + 1;
                }
            }
        }
    }

    Individual* KMIndividual::copy() const {
        return new KMIndividual(*this);
    }
} // NGroupingChallenge