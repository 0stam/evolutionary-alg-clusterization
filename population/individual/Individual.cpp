#include "Individual.h"

#include <iostream>
#include <tuple>

namespace NGroupingChallenge {
    Individual::Individual(int numberOfPoints, std::mt19937& randomEngine, std::uniform_int_distribution<>& groupRange)
        : genes(numberOfPoints)
        , score(-1)
        , genesEvaluated(false)
    {
        for (int i = 0; i < numberOfPoints; ++i) {
            genes[i] = groupRange(randomEngine);
        }
    }

    Individual* Individual::copy() const {
        return new Individual(*this);
    }

    double Individual::evaluate(AbstractEvaluator& evaluator) {
        if (genesEvaluated) {
            return score;
        }

        return reEvaluate(evaluator);
    }

    double Individual::reEvaluate(AbstractEvaluator& evaluator) {
        score = evaluator.evaluate(genes);
        genesEvaluated = true;

        return score;
    }

    // Placeholder implementation, override in children classes
    std::pair<Individual*, Individual*> Individual::cross(const Individual& other, std::mt19937& randomEngine, std::uniform_int_distribution<>& crossAtRange, AbstractEvaluator& evaluator) const {
        return {this->copy(), other.copy()};
    }

    void Individual::mutate(MutationStrategy& mutationStrategy) {
        genes = mutationStrategy.mutate(genes);
        genesEvaluated = false;
    }

    bool Individual::optimize(MutationStrategy& mutationStrategy, AbstractEvaluator& evaluator, int iterations) {
        std::vector<int> newGenes = genes;
        double newScore = evaluate(evaluator);

        for (int i = 0; i < iterations; ++i) {
            int changeIdx;
            int oldVal;

            std::tie(changeIdx, oldVal) = mutationStrategy.modify(newGenes);

            double prevScore = newScore;
            newScore = evaluator.calcDiff(newGenes, score, changeIdx, oldVal);

            //std::cout << newScore << " vs " << evaluator.evaluate(newGenes) << std::endl;

            if (newScore > prevScore) {
                newGenes[changeIdx] = oldVal;
                newScore = prevScore;
            }
        }

        if (newScore < score) {
            genes = newGenes;
            score = newScore;
            return true;
        }

        return false;
    }

    void Individual::normalize(const std::vector<int>& otherGenes) {
        
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

        genesEvaluated = false;
    }

    std::ostream& operator<<(std::ostream& ostream, const Individual& individual)  {
        ostream << individual.toString();

        return ostream;
    }
} // NGroupingChallenge
