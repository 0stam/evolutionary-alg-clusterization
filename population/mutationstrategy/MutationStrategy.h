#ifndef MUTATIONSTRATEGY_H
#define MUTATIONSTRATEGY_H
#include <vector>
#include <string>

namespace NGroupingChallenge {

class MutationStrategy {
public:
    virtual ~MutationStrategy() = default;

    virtual std::vector<int> mutate(std::vector<int> genes) = 0;
};

} // NGroupingChallenge

#endif //MUTATIONSTRATEGY_H
