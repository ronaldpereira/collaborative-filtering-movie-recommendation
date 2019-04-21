#include <iostream>
#include "libs/useritem.hpp"
#include "libs/prediction.hpp"

int main(int argc, char **argv)
{
    UserItem useritem;
    Prediction prediction;

    std::cout << "started matrix" << std::endl;

    useritem.MatrixBuilder(argv[1]);

    std::cout << "finished matrix" << std::endl;

    std::cout << "nitems: " << useritem.nItem << std::endl;

    std::cout << "started get" << std::endl;

    prediction.GetPredictions(argv[2], &useritem);

    std::cout << "finished get" << std::endl;

    return 0;
}
