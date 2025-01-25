#ifndef SOLUTIONSMANAGER_H
#define SOLUTIONSMANAGER_H
#include <random>
#include <vector>

#include "../GroupingEvaluator.h"
#include "evaluator/AbstractEvaluator.h"
#include "evaluator/ScoreSavingEvalWrapper.h"
#include "individual/Individual.h"
#include "selectionstrategy/SelectionStrategy.h"


namespace NGroupingChallenge {
    class PopulationManager {
    public:
        static const int TOURNAMENT_CANDIDATES;
        static const double CROSS_PROBABILITY;
        static const double MUTATION_PROBABILITY;
        static const int THREAD_COUNT;

        PopulationManager(CGroupingEvaluator& evaluator, int numberOfPoints, int numberOfGroups, int populationSize);
        ~PopulationManager();

        void initPopulation();

        void iteration();

        bool nextAction();

        bool crossover(Individual* fst, Individual* snd);
        bool passForward(Individual* fst, Individual* snd);

        bool passToNextGen(Individual* individual);

        void mutate();

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

        SelectionStrategy* selectionStrategy;
        MutationStrategy* mutationStrategy;
    };

    class PopulationThreadContext {
    public:
        std::mt19937 randomEngine;
        std::uniform_int_distribution<> groupRange;
        std::uniform_int_distribution<> crossAtRange;
        std::uniform_int_distribution<> pointIdxRange;
        std::uniform_int_distribution<> individualIDRange;
        std::uniform_real_distribution<> zeroToOneRange;
    };
}



#endif //SOLUTIONSMANAGER_H
