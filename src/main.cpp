#include "libs/useritem.hpp"
#include "libs/prediction.hpp"

int main(int argc, char **argv)
{
    UserItem useritem;
    Prediction prediction;

    useritem.ItemuserRatingsBuilder(argv[1]);

    prediction.GetPredictions(argv[2], &useritem);

    return 0;
}
