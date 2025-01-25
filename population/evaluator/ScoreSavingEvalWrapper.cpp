//
// Created by rs on 25.01.25.
//

#include "ScoreSavingEvalWrapper.h"

#include <limits>

namespace NGroupingChallenge {
    ScoreSavingEvalWrapper::ScoreSavingEvalWrapper(AbstractEvaluator& baseEvaluator)
        : baseEvaluator(baseEvaluator)
        , bestScore(std::numeric_limits<double>::max())
        , ownsBase(false)
    {}

    ScoreSavingEvalWrapper::ScoreSavingEvalWrapper(AbstractEvaluator&& baseEvaluator)
        : baseEvaluator(baseEvaluator.copy())
        , bestScore(std::numeric_limits<double>::max())
        , ownsBase(true)
    {}

    ScoreSavingEvalWrapper::ScoreSavingEvalWrapper(const ScoreSavingEvalWrapper& other)
        : baseEvaluator(other.ownsBase ? other.baseEvaluator.copy() : other.baseEvaluator)
        , bestScore(other.bestScore)
        , ownsBase(other.ownsBase)
    {}

    ScoreSavingEvalWrapper::~ScoreSavingEvalWrapper() {
        if (ownsBase) {
            delete &baseEvaluator;
        }
    }

    AbstractEvaluator& ScoreSavingEvalWrapper::copy() {
        return *new ScoreSavingEvalWrapper(*this);
    }

    double ScoreSavingEvalWrapper::evaluate(std::vector<int> solution) {
        double score = baseEvaluator.evaluate(solution);

        checkBest(solution, score);

        return score;
    }

    double ScoreSavingEvalWrapper::calcDiff(std::vector<int> solution, double prevScore, int changeIdx, int prevVal) {
        double score = baseEvaluator.calcDiff(solution, prevScore, changeIdx, prevVal);

        checkBest(solution, score);

        return score;
    }

    const std::vector<int>& ScoreSavingEvalWrapper::getBest() {
        return best;
    }

    double ScoreSavingEvalWrapper::getBestScore() {
        return bestScore;
    }

    void ScoreSavingEvalWrapper::checkBest(const std::vector<int>& solution, double score) {
        if (score < bestScore) {
            best = solution;
            bestScore = score;
        }
    }
} // NGroupingChallenge