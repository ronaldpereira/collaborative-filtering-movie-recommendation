#ifndef COSINESIM
#define COSINESIM
#include <vector>
#include <unordered_map>
#include "useritem.hpp"

class CosineSimilarity
{
private:
    // Data
    std::vector<std::vector<double>> itemSimilarity;

    // Methods
    std::unordered_map<int, double> calculateSimilarity(UserItem *, int);

public:
    std::vector<std::vector<double>> getTopNSimilarities(int, int);
};

#endif
