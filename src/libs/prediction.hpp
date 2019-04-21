#ifndef PREDICTION
#define PREDICTION
#include <unordered_map>
#include "cosinesimilarity.hpp"
#include "useritem.hpp"

class Prediction
{
private:
    double makePrediction(int, int, UserItem *, CosineSimilarity *);
    double getItemMean(int, UserItem *);

public:
    void GetPredictions(char *, UserItem *);
};

#endif
