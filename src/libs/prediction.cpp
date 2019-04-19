#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "prediction.hpp"
#include "useritem.hpp"

void Prediction::GetPredictions(char *targetsPath, UserItem *useritem)
{
    double ratingPrediction = 0;
    std::string line;
    std::ifstream targetsFile;
    targetsFile.open(targetsPath);

    // Discard header from csv
    getline(targetsFile, line);

    // Print header
    std::cout << "UserId:ItemId,Prediction" << std::endl;

    while (getline(targetsFile, line) && !line.empty())
    {
        char *token;

        char *cstr = new char[line.length() + 1];
        std::strcpy(cstr, line.c_str());

        token = strtok(cstr, ",ui");
        int user = atoi(token);

        token = strtok(NULL, ",ui");
        int item = atoi(token);

        ratingPrediction = makePrediction(user, item, useritem);

        std::cout << "u" << std::setfill('0') << std::setw(7) << user;
        std::cout << ":i" << std::setfill('0') << std::setw(7) << item;
        std::cout << "," << std::setprecision(15) << ratingPrediction;
        std::cout << std::endl;
    }

    targetsFile.close();
}

double Prediction::makePrediction(int userID, int itemID, UserItem *useritem)
{
    return getItemMean(itemID, useritem);
}

double Prediction::getItemMean(int itemID, UserItem *useritem)
{
    int itemPos = useritem->getItemPosition(itemID);
    double ratingMean;
    double ratingSum = 0;
    double nonZeroRatings = 0;

    if (itemPos >= 0)
    {
        for (unsigned int i = 0; i < useritem->matrix.size(); i++)
        {
            if (useritem->matrix[i][itemPos] >= 0)
            {
                nonZeroRatings++;
                ratingSum += useritem->matrix[i][itemPos];
            }
        }

        ratingMean = ratingSum / nonZeroRatings;

        return ratingMean;
    }

    return 0;
}
