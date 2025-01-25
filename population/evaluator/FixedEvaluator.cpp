//
// Created by rs on 25.01.25.
//

#include "FixedEvaluator.h"

namespace NGroupingChallenge {

    FixedEvaluator::FixedEvaluator(CGroupingEvaluator& baseEvaluator)
        : points(baseEvaluator.vGetPoints())
    {}

    AbstractEvaluator& FixedEvaluator::copy() {
        return *new FixedEvaluator(*this);
    }

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

    double FixedEvaluator::calcDiff(std::vector<int> solution, double prevScore, int changeIdx, int prevVal) {
        for (int i = 0; i < solution.size(); ++i) {
            if (i != changeIdx && solution[i] == prevVal) {
                prevScore -= distanceBetween(i, changeIdx);
            }
        }

        for (int i = 0; i < solution.size(); ++i) {
            if (i != changeIdx && solution[i] == solution[changeIdx]) {
                prevScore += distanceBetween(i, changeIdx);
            }
        }

        return prevScore;
    }

    double FixedEvaluator::distanceBetween(int fstPointIdx, int sndPointIdx) {
        return points[fstPointIdx].dCalculateDistance(points[sndPointIdx]);
    }
}
