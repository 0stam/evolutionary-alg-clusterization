#include <iostream>
#include <random>
#include <tuple>

#include "population/individual/Individual.h"
#include "population/individual/SinglePointCrossingIndividual.h"
#include "population/mutationstrategy/RandomGeneMutationStrategy.h"

using namespace NGroupingChallenge;

int disabled_main() {
    /*std::random_device randomDevice;
    std::mt19937 randomEngine(randomDevice());

    int numberOfPoints = 10;
    std::uniform_int_distribution<> groupRange(1, 8);
    std::uniform_int_distribution<> pointIdxRange(0, numberOfPoints - 1);
    std::uniform_int_distribution<> crossAtRange(1, numberOfPoints - 1);

    SinglePointCrossingIndividual first(numberOfPoints, randomEngine, groupRange);
    SinglePointCrossingIndividual second(numberOfPoints, randomEngine, groupRange);

    std::cout << first << "\n" << second << "\n";

    RandomGeneMutationStrategy mutationStrategy(randomEngine, groupRange, pointIdxRange);

    Individual* newFirst;
    Individual* newSecond;

    std::tie(newFirst, newSecond) = first.cross(second, randomEngine, crossAtRange);

    std::cout << *newFirst << "\n" << *newSecond << "\n";

    delete newFirst;
    delete newSecond;

    std::vector<int> a(100);
    std::cout << a.size() << "\n";*/

    return 0;
}
