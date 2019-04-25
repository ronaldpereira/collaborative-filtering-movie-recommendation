#include "libs/useritem.hpp"
#include "libs/prediction.hpp"

int main(int argc, char **argv)
{
    // Unused parameter 'argc' warning suppression
    (void)argc;

    UserItem useritem;
    Prediction prediction;

    useritem.ItemuserRatingsBuilder(argv[1]);

    prediction.GetPredictions(argv[2], &useritem);

    return 0;
}
