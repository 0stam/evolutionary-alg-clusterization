#ifndef SOLUTIONSMANAGER_H
#define SOLUTIONSMANAGER_H
#include <random>
#include <vector>

#include "../GroupingEvaluator.h"
#include "evaluator/ScoreSavingEvalWrapper.h"
#include "individual/Individual.h"
#include "selectionstrategy/SelectionStrategy.h"
#include "threads/ThreadPool.h"


namespace NGroupingChallenge {

    class PopulationThreadContext {
    public:
        PopulationThreadContext(int startWriteIdx, int endWriteIdx, std::uniform_int_distribution<>& groupRange, std::uniform_int_distribution<>& crossAtRange,
            std::uniform_int_distribution<>& pointIdxRange, std::uniform_int_distribution<>& individualIDRange, std::uniform_real_distribution<>& zeroToOneRange,
            AbstractEvaluator& evaluator);

        ~PopulationThreadContext();

        int nextWriteIdx;
        int startWriteIdx; // Inclusive
        int endWriteIdx; // Exclusive

        bool preprocessing;

        std::mt19937 randomEngine;
        std::uniform_int_distribution<> groupRange;
        std::uniform_int_distribution<> crossAtRange;
        std::uniform_int_distribution<> pointIdxRange;
        std::uniform_int_distribution<> individualIDRange;
        std::uniform_int_distribution<> individualThreadIDRange;
        std::uniform_real_distribution<> zeroToOneRange;

        SelectionStrategy* selectionStrategy;
        MutationStrategy* mutationStrategy;
    };


    class PopulationManager {
    public:
        static const int POPULATION_SIZE;
        static const int TOURNAMENT_CANDIDATES;
        static const double CROSS_PROBABILITY;
        static const double MUTATION_PROBABILITY;
        static const int THREAD_COUNT;
        static const int PREPROCESS_ITERATIONS;

        PopulationManager(CGroupingEvaluator& evaluator, int numberOfPoints, int numberOfGroups, int populationSize = POPULATION_SIZE);
        ~PopulationManager();

        void threadPreprocess(int iterations, PopulationThreadContext& tc);

        void iteration();

        std::vector<int> getBest() const;

        double getBestScore() const;
        double updateBestScore();

    private:
        std::vector<Individual*>* population;
        std::vector<Individual*>* nextGenPopulation;

        double crossProbability;
        double mutationProbability;

        Individual* best;
        double bestScore;

        bool preprocessing;

        AbstractEvaluator& evaluator;
        CGroupingEvaluator& baseEvaluator;

        int threadCount;
        ThreadPool threadPool;
        std::vector<PopulationThreadContext*> threadContexts;

        std::mt19937 randomEngine;
        std::uniform_int_distribution<> groupRange;
        std::uniform_int_distribution<> crossAtRange;
        std::uniform_int_distribution<> pointIdxRange;
        std::uniform_int_distribution<> individualIDRange;
        std::uniform_real_distribution<> zeroToOneRange;

        int numberOfPoints;
        int numberOfGroups;
        int populationSize;

        int nextWriteIdx;

        void initPopulation();
        void initPopulationChunk(PopulationThreadContext& tc);
        void initThreadContexts();

        void expandPopulation(int times);

        void preprocessIteration();

        void geneticIteration();
        void threadIteration(PopulationThreadContext& tc);

        bool nextAction(PopulationThreadContext& tc);

        bool crossover(Individual* fst, Individual* snd, PopulationThreadContext& tc);
        bool passForward(Individual* fst, Individual* snd, PopulationThreadContext& tc);

        bool passToNextGen(Individual* individual, PopulationThreadContext& tc);

        void mutate(PopulationThreadContext& tc);
        void evaluateNextGen(PopulationThreadContext& tc);
        void reEvaluateCurrent(PopulationThreadContext& tc);
        void normalize(Individual* individual, PopulationThreadContext& tc);
    };
}



#endif //SOLUTIONSMANAGER_H
