//
// Created by rs on 25.01.25.
//

#include "FixedEvaluator.h"

namespace NGroupingChallenge {

    FixedEvaluator::FixedEvaluator(CGroupingEvaluator& baseEvaluator)
        : points(baseEvaluator.vGetPoints())
    {}

    double FixedEvaluator::evaluate(std::vector<int> solution) {
        double result = 0;

        for (int i = 0; i < solution.size() - 1; ++i) {
            for (int j = i + 1; j < solution.size(); ++j) {
                if (solution[i] == solution[j]) {
                    result += distanceBetween(i, j);
                }
            }
        }

        return result;
    }

    double FixedEvaluator::reEvaluate(std::vector<int> solution, int changeIdx, int prevVal) {
        // TODO: implement
        return 0;
    }

    double FixedEvaluator::distanceBetween(int fstPointIdx, int sndPointIdx) {
        return points[fstPointIdx].dCalculateDistance(points[sndPointIdx]);
    }
}
