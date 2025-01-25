#include "Individual.h"

namespace NGroupingChallenge {
    Individual::Individual(int numberOfPoints, std::mt19937& randomEngine, std::uniform_int_distribution<>& groupRange)
        : genes(numberOfPoints)
    {
        for (int i = 0; i < numberOfPoints; ++i) {
            genes[i] = groupRange(randomEngine);
        }
    }

    Individual* Individual::copy() const {
        return new Individual(*this);
    }

    double Individual::evaluate(AbstractEvaluator& evaluator) const {
        return evaluator.evaluate(genes);
    }

    // Placeholder implementation, override in children classes
    std::pair<Individual*, Individual*> Individual::cross(const Individual& other, std::mt19937& randomEngine, std::uniform_int_distribution<>& crossAtRange) const {
        return {this->copy(), other.copy()};
    }

    Individual* Individual::mutate(MutationStrategy& mutationStrategy) const {
        Individual* result = this->copy();
        result->genes = mutationStrategy.mutate(genes);

        return result;
    }

    std::string Individual::toString() const {
        std::string result;

        for (int gene : genes) {
            result += std::to_string(gene);
        }

        return result;
    }

    const std::vector<int>& Individual::getGenes() const {
        return genes;
    }

    void Individual::setGenes(const std::vector<int>& genes) {
        this->genes = genes;
    }

    std::ostream& operator<<(std::ostream& ostream, const Individual& individual)  {
        ostream << individual.toString();

        return ostream;
    }
} // NGroupingChallenge
