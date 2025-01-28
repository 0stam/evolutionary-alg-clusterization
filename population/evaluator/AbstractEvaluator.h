//
// Created by rs on 25.01.25.
//

#ifndef ABSTRACTEVALUATOR_H
#define ABSTRACTEVALUATOR_H
#include <vector>


class AbstractEvaluator {
public:
    virtual ~AbstractEvaluator() = default;

    virtual AbstractEvaluator& copy() = 0;

    virtual double evaluate(std::vector<int> solution) = 0;
    virtual double calcDiff(std::vector<int> solution, double prevScore, int changeIdx, int prevVal) = 0;

    virtual double distanceBetween(int fstPointIdx, int sndPointIdx) = 0;
};



#endif //ABSTRACTEVALUATOR_H
