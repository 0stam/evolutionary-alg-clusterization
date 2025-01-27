#include "Optimizer.h"

#include <iomanip>

using namespace NGroupingChallenge;

COptimizer::COptimizer(CGroupingEvaluator& cEvaluator)
	: c_evaluator(cEvaluator)
{
	random_device c_seed_generator;
	c_random_engine.seed(c_seed_generator());
}

COptimizer::~COptimizer() {
	delete populationManager;
}

void COptimizer::vInitialize()
{
	populationManager = new PopulationManager(c_evaluator, c_evaluator.iGetNumberOfPoints(), c_evaluator.iGetUpperBound());

	v_current_best = populationManager->getBest();
	d_current_best_fitness = populationManager->getBestScore();
}

void COptimizer::vRunIteration()
{
	populationManager->iteration();
	v_current_best = populationManager->getBest();
	d_current_best_fitness = populationManager->getBestScore();

	// TODO: Remove
	std::cout << std::setprecision(15) << populationManager->getBestScore() << "\n";
}