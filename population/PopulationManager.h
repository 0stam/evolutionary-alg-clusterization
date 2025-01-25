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
        static const int TOURNAMENT_CANDIDATES;
        static const double CROSS_PROBABILITY;
        static const double MUTATION_PROBABILITY;
        static const int THREAD_COUNT;

        PopulationManager(CGroupingEvaluator& evaluator, int numberOfPoints, int numberOfGroups, int populationSize);
        ~PopulationManager();

        void initPopulation();
        void initThreadContexts();

        void iteration();
        void threadIteration(PopulationThreadContext& tc);

        bool nextAction(PopulationThreadContext& tc);

        bool crossover(Individual* fst, Individual* snd, PopulationThreadContext& tc);
        bool passForward(Individual* fst, Individual* snd, PopulationThreadContext& tc);

        bool passToNextGen(Individual* individual, PopulationThreadContext& tc);

        void mutate(PopulationThreadContext& tc);

        double getBestScore() const;
        double updateBestScore();

    private:
        std::vector<Individual*>* population;
        std::vector<Individual*>* nextGenPopulation;

        double crossProbability;
        double mutationProbability;

        Individual* best;
        double bestScore;

        ScoreSavingEvalWrapper& evaluator;
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
    };
}



#endif //SOLUTIONSMANAGER_H
