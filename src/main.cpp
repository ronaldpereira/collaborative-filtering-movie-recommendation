#include "libs/itemuser.hpp"
#include "libs/prediction.hpp"

int main(int argc, char **argv)
{
    // Unused parameter 'argc' warning suppression
    (void)argc;

    // K Nearest Neighbors selection
    int kNearestNeighbors = 0;

    ItemUser itemuser;
    Prediction prediction;

    itemuser.ItemUserRatingsBuilder(argv[1]);

    prediction.GetPredictions(argv[2], &itemuser, kNearestNeighbors);

    return 0;
}
