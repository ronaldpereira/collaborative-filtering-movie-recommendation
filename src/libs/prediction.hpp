#ifndef PREDICTION
#define PREDICTION
#include "cosinesimilarity.hpp"
#include "itemuser.hpp"

class Prediction
{
private:
    double makePrediction(int, int, ItemUser *, CosineSimilarity *, int);

public:
    void GetPredictions(char *, ItemUser *, int);
};

#endif
