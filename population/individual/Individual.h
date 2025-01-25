#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H
#include <random>
#include <vector>

#include "../../GroupingEvaluator.h"
#include "../evaluator/AbstractEvaluator.h"
#include "../mutationstrategy/MutationStrategy.h"

namespace NGroupingChallenge {

class Individual {
public:
    Individual(int numberOfPoints, std::mt19937& randomEngine, std::uniform_int_distribution<>& groupRange);
    virtual ~Individual() = default;

    virtual Individual* copy() const;

    double evaluate(AbstractEvaluator& evaluator) const;
    virtual std::pair<Individual*, Individual*> cross(const Individual& other, std::mt19937& randomEngine, std::uniform_int_distribution<>& crossAtRange) const;  // Default implementation, should be changed in subclasses
    Individual* mutate(MutationStrategy& mutationStrategy) const;

    const std::vector<int>& getGenes() const;
    void setGenes(const std::vector<int>& genes);

    std::string toString() const;

protected:
    std::vector<int> genes;
};

std::ostream& operator<<(std::ostream& ostream, const Individual& individual);

} // NGroupingChallenge

#endif //INDIVIDUAL_H
