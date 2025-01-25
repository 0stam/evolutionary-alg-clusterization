//
// Created by rs on 25.01.25.
//

#ifndef ABSTRACTEVALUATOR_H
#define ABSTRACTEVALUATOR_H
#include <vector>


class AbstractEvaluator {
public:
    virtual ~AbstractEvaluator() = default;

    virtual double evaluate(std::vector<int> solution) = 0;
    virtual double reEvaluate(std::vector<int> solution, int changeIdx, int prevVal) = 0;
    virtual double distanceBetween(int fstPointIdx, int sndPointIdx) = 0;
};



#endif //ABSTRACTEVALUATOR_H
