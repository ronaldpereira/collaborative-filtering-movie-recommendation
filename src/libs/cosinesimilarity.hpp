#ifndef COSINESIM
#define COSINESIM
#include <vector>
#include <array>
#include "useritem.hpp"

class CosineSimilarity
{
private:
    // Data
    std::vector<std::vector<double>> itemSimilarity;

    // Methods
    double calculateSimilarity(std::vector<int>, std::vector<int>);

public:
    void PreComputeSimilarities(UserItem *);
    std::vector<std::vector<double>> getTopNSimilarities(int, int);
};

#endif
