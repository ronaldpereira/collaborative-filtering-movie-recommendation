#ifndef OPERATIONS
#define OPERATIONS
#include <vector>
#include "useritem.hpp"

class CosineSimilarity
{
private:
    // Data
    std::vector<std::vector<int>> itemSimilarity;

    // Methods
    double calculateSimilarity(std::vector<int>, std::vector<int>);

public:
    void PreComputeSimilarities(UserItem *);
    std::vector<std::vector<int>> GetItemNeighbors(int, int);
};

#endif
