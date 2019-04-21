#ifndef PREDICTION
#define PREDICTION
#include "cosinesimilarity.hpp"
#include "useritem.hpp"

class Prediction
{
private:
    double makePrediction(int, int, UserItem *, CosineSimilarity *);

public:
    void GetPredictions(char *, UserItem *);
};

#endif
