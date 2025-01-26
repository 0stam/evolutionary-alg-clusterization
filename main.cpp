#include <iostream>
#include <random>
#include <tuple>

#include "population/evaluator/FixedEvaluator.h"
#include "population/individual/Individual.h"
#include "population/individual/SinglePointCrossingIndividual.h"
#include "population/mutationstrategy/RandomGeneMutationStrategy.h"

using namespace NGroupingChallenge;

int d_main() {
    // Create vector of four 2d double coordinates
    std::vector<std::pair<double, double>> points = {
            {0, 0},
            {1, 1},
            {2, 2},
            {3, 3}
    };

    // Create CPoint objects from the vector
    std::vector<CPoint> cPoints;
    for (const auto& point : points) {
        CPoint cPoint;
        cPoint.vAddCoordinate(point.first);
        cPoint.vAddCoordinate(point.second);

        cPoints.push_back(cPoint);
    }

    CGroupingEvaluator cGroupingEvaluator(3, cPoints);
    FixedEvaluator fixedEvaluator(cGroupingEvaluator);

    double score = fixedEvaluator.evaluate({0, 0, 0, 1});
    double newScore = fixedEvaluator.calcDiff({0, 1, 0, 1}, score, 1, 0);
    double newAbsoluteScore = fixedEvaluator.evaluate({0, 1, 0, 1});

    std::cout << newScore << " vs " << newAbsoluteScore << std::endl;

    return 0;
}
