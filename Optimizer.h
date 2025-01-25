#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "GroupingEvaluator.h"

#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include "population/PopulationManager.h"

using namespace std;

namespace NGroupingChallenge
{
	class COptimizer
	{
	public:
		COptimizer(CGroupingEvaluator& cEvaluator);
		~COptimizer();

		void vInitialize();
		void vRunIteration();

		vector<int>* pvGetCurrentBest() { return &v_current_best; }

	private:
		CGroupingEvaluator& c_evaluator; 

		double d_current_best_fitness;
		vector<int> v_current_best;

		mt19937 c_random_engine;

		PopulationManager* populationManager;
	};
}

#endif