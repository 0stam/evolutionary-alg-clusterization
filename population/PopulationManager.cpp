#include "PopulationManager.h"

#include <algorithm>
#include <functional>
#include <iostream>

#include "evaluator/FixedEvaluator.h"
#include "individual/SinglePointCrossingIndividual.h"
#include "mutationstrategy/RandomGeneMutationStrategy.h"
#include "selectionstrategy/TournamentSelectionStrategy.h"

namespace NGroupingChallenge {
    const int PopulationManager::TOURNAMENT_CANDIDATES = 1;
    const double PopulationManager::CROSS_PROBABILITY = 0.7;
    const double PopulationManager::MUTATION_PROBABILITY = 0.05;
    const int PopulationManager::THREAD_COUNT = 1;

    PopulationThreadContext::PopulationThreadContext(int startWriteIdx, int endWriteIdx, std::uniform_int_distribution<>& groupRange,
        std::uniform_int_distribution<>& crossAtRange, std::uniform_int_distribution<>& pointIdxRange,
        std::uniform_int_distribution<>& individualIDRange, std::uniform_real_distribution<>& zeroToOneRange, AbstractEvaluator& evaluator)
            : nextWriteIdx(startWriteIdx)
            , startWriteIdx(startWriteIdx)
            , endWriteIdx(endWriteIdx)
            , groupRange(groupRange)
            , crossAtRange(crossAtRange)
            , pointIdxRange(pointIdxRange)
            , individualIDRange(individualIDRange)
            , individualThreadIDRange(startWriteIdx, endWriteIdx - 1)
            , zeroToOneRange(zeroToOneRange)
            , selectionStrategy(new TournamentSelectionStrategy(this->randomEngine, this->individualIDRange, evaluator, PopulationManager::TOURNAMENT_CANDIDATES))
            , mutationStrategy(new RandomGeneMutationStrategy(this->randomEngine, this->groupRange, this->pointIdxRange))
    {
        std::random_device rd;
        randomEngine.seed(rd());
    }

    PopulationThreadContext::~PopulationThreadContext() {
        delete selectionStrategy;
        delete mutationStrategy;
    }

    PopulationManager::PopulationManager(CGroupingEvaluator& evaluator, int numberOfPoints, int numberOfGroups, int populationSize)
        : population(new std::vector<Individual*>(populationSize))
        , nextGenPopulation(new std::vector<Individual*>(populationSize, nullptr))
        , crossProbability(CROSS_PROBABILITY)
        , mutationProbability(MUTATION_PROBABILITY)
        , best(nullptr)
        , bestScore(std::numeric_limits<double>::max())
        , evaluator(*new FixedEvaluator(evaluator))
        , baseEvaluator(evaluator)
        , threadCount(THREAD_COUNT)
        , threadPool(THREAD_COUNT)
        , threadContexts(THREAD_COUNT)
        , groupRange(1, numberOfGroups)
        , crossAtRange(1, numberOfPoints - 1)
        , pointIdxRange(0, numberOfPoints - 1)
        , individualIDRange(0, populationSize - 1)
        , zeroToOneRange(0, 1)
        , numberOfPoints(numberOfPoints)
        , numberOfGroups(numberOfGroups)
        , populationSize(populationSize)
        , nextWriteIdx(0)
    {
        std::random_device rd;
        randomEngine.seed(rd());

        initPopulation();
        initThreadContexts();
    }


    PopulationManager::~PopulationManager() {
        for (int i = 0; i < populationSize; ++i) {
            delete (*population)[i];
            delete (*nextGenPopulation)[i];
        }

        delete &evaluator;
        delete best;
    }

    void PopulationManager::initPopulation() {
        for (int i = 0; i < populationSize; ++i) {
            (*population)[i] = new SinglePointCrossingIndividual(numberOfPoints, randomEngine, groupRange);
        }
    }

    void PopulationManager::initThreadContexts() {
        int chunkSize = populationSize / threadCount;

        for (int i = 0; i < threadCount; ++i) {
            int startIdx = i * chunkSize;
            int endIdx = startIdx + chunkSize;

            //std::cout << startIdx << ", " << endIdx << "\n";

            if (i == threadCount - 1) {
                endIdx = populationSize;
            }

            threadContexts[i] = new PopulationThreadContext(startIdx, endIdx, groupRange, crossAtRange, pointIdxRange, individualIDRange, zeroToOneRange, evaluator);
        }
    }

    void PopulationManager::iteration() {
        for (auto context : threadContexts) {
            threadPool.enqueue([this, context] { threadIteration(*context); });
        }

        threadPool.join();

        //std::cout << "Iteration finished" << "\n";

        std::swap(population, nextGenPopulation);

        updateBestScore();

        nextWriteIdx = 0;
    }

    void PopulationManager::threadIteration(PopulationThreadContext& tc) {
        while (nextAction(tc)) {}

        tc.nextWriteIdx = tc.startWriteIdx;
        mutate(tc);

        tc.nextWriteIdx = tc.startWriteIdx;

        //std::cout << "Thread finished" << std::endl;
    }

    bool PopulationManager::nextAction(PopulationThreadContext& tc) {
        //std::cout << tc.nextWriteIdx << "\n";

        Individual* fst = tc.selectionStrategy->select(*population);
        Individual* snd = tc.selectionStrategy->select(*population);

        if (tc.zeroToOneRange(randomEngine) < crossProbability) {
            return crossover(fst, snd, tc);
        }

        return passForward(fst, snd, tc);
    }

    bool PopulationManager::crossover(Individual* fst, Individual* snd, PopulationThreadContext& tc) {
        Individual* newFst;
        Individual* newSnd;

        std::tie(newFst, newSnd) = fst->cross(*snd, tc.randomEngine, tc.crossAtRange, evaluator);

        if (!passToNextGen(newFst, tc)) {
            return false;
        }

        return passToNextGen(newSnd, tc);
    }

    bool PopulationManager::passForward(Individual* fst, Individual* snd, PopulationThreadContext& tc) {
        if (!passToNextGen(fst->copy(), tc)) {
            return false;
        }

        return passToNextGen(snd->copy(), tc);
    }

    bool PopulationManager::passToNextGen(Individual* individual, PopulationThreadContext& tc) {
        delete (*nextGenPopulation)[tc.nextWriteIdx];

        (*nextGenPopulation)[tc.nextWriteIdx] = individual;

        updateBestScore();

        return ++tc.nextWriteIdx < tc.endWriteIdx;
    }

    void PopulationManager::mutate(PopulationThreadContext& tc) {
        //std::cout << tc.nextWriteIdx << "\n";
        int mutationCount = std::ceil(mutationProbability * numberOfPoints * populationSize / threadCount);

        for (int i = 0; i < mutationCount; ++i) {
            int idx = tc.individualThreadIDRange(tc.randomEngine);

            (*nextGenPopulation)[idx]->mutate(*tc.mutationStrategy);
        }
    }

    double PopulationManager::getBestScore() const {
        return bestScore;
    }

    double PopulationManager::updateBestScore() {
        for (auto individual : *population) {
            double score = individual->evaluate(evaluator);

            if (score < bestScore) {
                best = individual->copy();
                bestScore = score;
            }
        }

        return bestScore;
    }
}
