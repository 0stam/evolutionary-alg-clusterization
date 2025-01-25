//
// Created by rs on 25.01.25.
//

#ifndef FIXEDEVALUATOR_H
#define FIXEDEVALUATOR_H
#include "AbstractEvaluator.h"
#include "../../GroupingEvaluator.h"

namespace NGroupingChallenge {

class FixedEvaluator : public AbstractEvaluator {
public:
    FixedEvaluator(CGroupingEvaluator& baseEvaluator);

    double evaluate(std::vector<int> solution) override;
    double reEvaluate(std::vector<int> solution, int changeIdx, int prevVal) override;
    double distanceBetween(int fstPointIdx, int sndPointIdx) override;

private:
    const std::vector<CPoint>& points;
};

}

#endif //FIXEDEVALUATOR_H
