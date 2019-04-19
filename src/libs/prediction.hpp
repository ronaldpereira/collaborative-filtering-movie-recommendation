#ifndef PREDICTION
#define PREDICTION
#include <vector>
#include "useritem.hpp"

class Prediction
{
private:
    double makePrediction(int, int, UserItem*);
    double getItemMean(int, UserItem*);
public:
    void GetPredictions(char*, UserItem*);
};

#endif
