cmake_minimum_required(VERSION 3.30)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main.cpp
        GaussianGroupingEvaluatorFactory.cpp
        GaussianGroupingEvaluatorFactory.h
        GroupingChallenge.cpp
        GroupingEvaluator.cpp
        GroupingEvaluator.h
        Optimizer.cpp
        Optimizer.h
        Point.cpp
        Point.h
        population/PopulationManager.cpp
        population/PopulationManager.h
        population/individual/Individual.cpp
        population/individual/Individual.h
        population/mutationstrategy/MutationStrategy.cpp
        population/mutationstrategy/MutationStrategy.h
        population/individual/SinglePointCrossingIndividual.cpp
        population/individual/SinglePointCrossingIndividual.h
        population/mutationstrategy/RandomGeneMutationStrategy.cpp
        population/mutationstrategy/RandomGeneMutationStrategy.h
        population/selectionstrategy/SelectionStrategy.cpp
        population/selectionstrategy/SelectionStrategy.h
        population/selectionstrategy/TournamentSelectionStrategy.cpp
        population/selectionstrategy/TournamentSelectionStrategy.h
        population/evaluator/FixedEvaluator.cpp
        population/evaluator/FixedEvaluator.h
        population/evaluator/AbstractEvaluator.cpp
        population/evaluator/AbstractEvaluator.h
        population/evaluator/ScoreSavingEvalWrapper.cpp
        population/evaluator/ScoreSavingEvalWrapper.h)
