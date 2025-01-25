#ifndef SCORESAVINGEVALWRAPPER_H
#define SCORESAVINGEVALWRAPPER_H
#include "AbstractEvaluator.h"

namespace NGroupingChallenge {

class ScoreSavingEvalWrapper : public AbstractEvaluator {
public:
    ScoreSavingEvalWrapper(AbstractEvaluator& baseEvaluator);
    ScoreSavingEvalWrapper(AbstractEvaluator&& baseEvaluator);
    ScoreSavingEvalWrapper(const ScoreSavingEvalWrapper& other);

    ~ScoreSavingEvalWrapper();

    AbstractEvaluator& copy() override;

    double evaluate(std::vector<int> solution) override;
    double calcDiff(std::vector<int> solution, double prevScore, int changeIdx, int prevVal) override;

    const std::vector<int>& getBest();
    double getBestScore();

private:
    AbstractEvaluator& baseEvaluator;

    std::vector<int> best;
    double bestScore;

    bool ownsBase;

    void checkBest(const std::vector<int>& solution, double score);
};

} // NGroupingChallenge

#endif //SCORESAVINGEVALWRAPPER_H
