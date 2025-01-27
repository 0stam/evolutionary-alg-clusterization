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

    void Individual::requireEval() {
        genesEvaluated = false;
    }

    // Placeholder implementation, override in children classes
    std::pair<Individual*, Individual*> Individual::cross(Individual& other, std::mt19937& randomEngine, std::uniform_int_distribution<>& crossAtRange, AbstractEvaluator& evaluator) const {
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

    void Individual::normalize(const std::vector<int>& otherGenes, int numberOfGroups) {
        int counts[numberOfGroups + 1][numberOfGroups + 1];
        int mapTo[numberOfGroups + 1]; // idx: this group, value: other group

        for (int i = 0; i < numberOfGroups + 1; ++i) {
            for (int j = 0; j < numberOfGroups + 1; ++j) {
                counts[i][j] = 0;
            }
        }

        for (int i = 0; i < numberOfGroups + 1; ++i) {
            mapTo[i] = -1;
        }

        for (int i = 0; i < genes.size(); ++i) {
            counts[genes[i]][otherGenes[i]]++;
        }

        for (int i = 1; i < numberOfGroups + 1; ++i) {
            int maxIdx = -1;
            int maxCount = -1;

            for (int j = 1; j < numberOfGroups + 1; ++j) {
                if (counts[i][j] > maxCount) {
                    bool alreadyMapped = false;

                    for (int k = 1; k < numberOfGroups + 1; ++k) {
                        if (mapTo[k] == j) {
                            alreadyMapped = true;
                            break;
                        }
                    }

                    if (!alreadyMapped) {
                        maxCount = counts[i][j];
                        maxIdx = j;
                    }
                }
            }

            mapTo[i] = maxIdx;
        }

        for (int& gene : genes) {
            gene = mapTo[gene];
        }

        genesEvaluated = false;
    }

    std::string Individual::toString() const {
        std::string result;

        for (int gene : genes) {
            result += std::to_string(gene);
        }

        return result;
    }

    std::vector<int>& Individual::getGenes() {
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
