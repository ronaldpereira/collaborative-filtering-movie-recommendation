#ifndef COSINESIM
#define COSINESIM
#include <unordered_map>
#include "useritem.hpp"

class CosineSimilarity
{
private:
    std::unordered_map<int, std::unordered_map<int, double>> computedSimilarities;

public:
    ~CosineSimilarity();
    std::unordered_map<int, double> calculateSimilarity(UserItem *, int);
};

#endif
