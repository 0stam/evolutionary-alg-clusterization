#include "GaussianGroupingEvaluatorFactory.h"
#include "GroupingEvaluator.h"
#include "Optimizer.h"
#include "population/exampleloader/CClusterSaver.h"
#include "population/exampleloader/CPointLoader.h"

using namespace NGroupingChallenge;

int main()
{
	CGaussianGroupingEvaluatorFactory c_evaluator_factory(4, 5000, 5);

	c_evaluator_factory
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0);

	std::vector<CPoint> points = CPointLoader::vLoadPointsFromCSV("/home/rs/CLionProjects/tep-konkurs/data/mopsi-finland.csv");

	//CGroupingEvaluator* pc_evaluator = c_evaluator_factory.pcCreateEvaluator(42);
	CGroupingEvaluator* pc_evaluator = new CGroupingEvaluator(3, points);

	COptimizer c_optimizer(*pc_evaluator);

	c_optimizer.vInitialize();

	CClusterSaver::vSaveClustersToCSV(*c_optimizer.pvGetCurrentBest(), "/home/rs/CLionProjects/tep-konkurs/data/result.txt");

	for (int i = 0; i < 1000000; i++)
	{
		c_optimizer.vRunIteration();
		CClusterSaver::vSaveClustersToCSV(*c_optimizer.pvGetCurrentBest(), "/home/rs/CLionProjects/tep-konkurs/data/result.txt");
	}

	delete pc_evaluator;

	return 0;
}