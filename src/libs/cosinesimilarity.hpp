#ifndef COSINESIM
#define COSINESIM
#include <vector>
#include <array>

class CosineSimilarity
{
private:
    // Data
    std::vector<std::vector<double>> itemSimilarity;

    // Methods
    double calculateSimilarity(std::vector<int>, std::vector<int>);

public:
    std::vector<std::vector<double>> getTopNSimilarities(int, int);
};

#endif
