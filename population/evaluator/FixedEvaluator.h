#ifndef FIXEDEVALUATOR_H
#define FIXEDEVALUATOR_H
#include "AbstractEvaluator.h"
#include "../../GroupingEvaluator.h"

namespace NGroupingChallenge {

class FixedEvaluator : public AbstractEvaluator {
public:
    FixedEvaluator(CGroupingEvaluator& baseEvaluator);

    AbstractEvaluator& copy() override;

    double evaluate(std::vector<int> solution) override;
    double calcDiff(std::vector<int> solution, double prevScore, int changeIdx, int prevVal) override;

protected:
    double distanceBetween(int fstPointIdx, int sndPointIdx);

private:
    const std::vector<CPoint>& points;
};

}

#endif //FIXEDEVALUATOR_H
