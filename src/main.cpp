#include "libs/useritem.hpp"
#include "libs/prediction.hpp"

int main(int argc, char **argv)
{
    // Unused parameter 'argc' warning suppression
    (void)argc;

    // K Nearest Neighbors
    int kNearestNeighbors = 0;

    UserItem useritem;
    Prediction prediction;

    useritem.ItemuserRatingsBuilder(argv[1]);

    prediction.GetPredictions(argv[2], &useritem, kNearestNeighbors);

    return 0;
}
