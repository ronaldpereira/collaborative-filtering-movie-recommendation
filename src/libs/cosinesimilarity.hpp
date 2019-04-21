#ifndef COSINESIM
#define COSINESIM
#include <vector>
#include <unordered_map>
#include "useritem.hpp"

class CosineSimilarity
{
public:
    std::unordered_map<int, double> calculateSimilarity(UserItem *, int);
};

#endif
