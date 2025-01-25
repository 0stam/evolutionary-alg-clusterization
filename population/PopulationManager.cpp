#include "PopulationManager.h"

#include <algorithm>
#include <functional>
#include <iostream>

#include "evaluator/FixedEvaluator.h"
#include "individual/SinglePointCrossingIndividual.h"
#include "mutationstrategy/RandomGeneMutationStrategy.h"
#include "selectionstrategy/TournamentSelectionStrategy.h"

namespace NGroupingChallenge {
    const int PopulationManager::TOURNAMENT_CANDIDATES = 2;
    const double PopulationManager::CROSS_PROBABILITY = 0.7;
    const double PopulationManager::MUTATION_PROBABILITY = 0.05;

    PopulationManager::PopulationManager(CGroupingEvaluator& evaluator, int numberOfPoints, int numberOfGroups, int populationSize)
        : population(new std::vector<Individual*>(populationSize))
        , nextGenPopulation(new std::vector<Individual*>(populationSize, nullptr))
        , crossProbability(CROSS_PROBABILITY)
        , best(nullptr)
        , bestScore(std::numeric_limits<double>::max())
        , evaluator(*new FixedEvaluator(evaluator))
        , baseEvaluator(evaluator)
        , groupRange(1, numberOfGroups)
        , crossAtRange(1, numberOfPoints - 1)
        , pointIdxRange(0, numberOfPoints - 1)
        , individualIDRange(0, populationSize - 1)
        , zeroToOneRange(0, 1)
        , numberOfPoints(numberOfPoints)
        , numberOfGroups(numberOfGroups)
        , populationSize(populationSize)
        , nextWriteIdx(0)
        , selectionStrategy(new TournamentSelectionStrategy(randomEngine, individualIDRange, this->evaluator, TOURNAMENT_CANDIDATES))
        , mutationStrategy(new RandomGeneMutationStrategy(randomEngine, groupRange, pointIdxRange))
    {
        std::random_device rd;
        randomEngine.seed(rd());

        initPopulation();
    }


    PopulationManager::~PopulationManager() {
        for (int i = 0; i < populationSize; ++i) {
            delete (*population)[i];
            delete (*nextGenPopulation)[i];
        }

        delete best;
        delete selectionStrategy;
        delete mutationStrategy;
    }

    void PopulationManager::initPopulation() {
        for (int i = 0; i < populationSize; ++i) {
            (*population)[i] = new SinglePointCrossingIndividual(numberOfPoints, randomEngine, groupRange);
        }
    }

    void PopulationManager::iteration() {
        while (nextAction()) {}
        mutate();

        std::swap(population, nextGenPopulation);

        nextWriteIdx = 0;
    }

    bool PopulationManager::nextAction() {
        Individual* fst = selectionStrategy->select(*population);
        Individual* snd = selectionStrategy->select(*population);

        if (zeroToOneRange(randomEngine) < crossProbability) {
            return crossover(fst, snd);
        }

        return passForward(fst, snd);
    }

    bool PopulationManager::crossover(Individual* fst, Individual* snd) {
        Individual* newFst;
        Individual* newSnd;

        std::tie(newFst, newSnd) = fst->cross(*snd, randomEngine, crossAtRange);

        if (!passToNextGen(newFst)) {
            return false;
        }

        return passToNextGen(newSnd);
    }

    bool PopulationManager::passForward(Individual* fst, Individual* snd) {
        if (!passToNextGen(fst->copy())) {
            return false;
        }

        return passToNextGen(snd->copy());
    }

    bool PopulationManager::passToNextGen(Individual* individual) {
        delete (*nextGenPopulation)[nextWriteIdx];

        (*nextGenPopulation)[nextWriteIdx] = individual;

        updateBestScore();

        return ++nextWriteIdx < populationSize;
    }

    void PopulationManager::mutate() {
        binomial_distribution<> a;
        int mutationCount = std::ceil(mutationProbability * numberOfPoints * populationSize);

        for (int i = 0; i < mutationCount; ++i) {
            int idx = individualIDRange(randomEngine);

            auto temp = (*nextGenPopulation)[idx];
            (*nextGenPopulation)[idx] = temp->mutate(*mutationStrategy);
            delete temp;
        }
    }

    double PopulationManager::getBestScore() const {
        return bestScore;
    }

    double PopulationManager::updateBestScore() {
        for (auto individual : *nextGenPopulation) {
            if (individual == nullptr) break;
            double currentScore = individual->evaluate(evaluator);

            if (currentScore < bestScore) {
                delete best;
                best = individual->copy();
                bestScore = currentScore;
            }
        }

        //std::cout << bestScore << ": " << *best << "\n";
        return bestScore;
    }
}
