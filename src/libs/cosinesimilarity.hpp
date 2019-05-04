#ifndef COSINESIM
#define COSINESIM
#include <unordered_map>
#include "itemuser.hpp"

class CosineSimilarity
{
private:
    // Data
    std::unordered_map<int, std::unordered_map<int, double>> computedSimilarities;

    // Methods
    std::unordered_map<int, double> getKNearestNeighbors(std::unordered_map<int, double> *, int);

public:
    std::unordered_map<int, double> calculateSimilarity(ItemUser *, int, int);
};

#endif
