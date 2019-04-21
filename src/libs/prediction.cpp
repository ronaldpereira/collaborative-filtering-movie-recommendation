#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <unordered_map>
#include "cosinesimilarity.hpp"
#include "prediction.hpp"
#include "useritem.hpp"

void Prediction::GetPredictions(char *targetsPath, UserItem *useritem)
{
    int user = 0, item = 0;
    char *token = NULL;
    double ratingPrediction = 0;
    std::string line;

    CosineSimilarity cossimilarity;

    std::ifstream targetsFile;
    targetsFile.open(targetsPath);

    // Discard header from csv
    getline(targetsFile, line);

    // Print header
    std::cout << "UserId:ItemId,Prediction" << std::endl;

    while (getline(targetsFile, line) && !line.empty())
    {
        char *cstr = new char[line.length() + 1];
        std::strcpy(cstr, line.c_str());

        token = strtok(cstr, ",ui");
        user = atoi(token);

        token = strtok(NULL, ",ui");
        item = atoi(token);

        ratingPrediction = makePrediction(user, item, useritem, &cossimilarity);

        std::cout << "u" << std::setfill('0') << std::setw(7) << user;
        std::cout << ":i" << std::setfill('0') << std::setw(7) << item;
        std::cout << "," << std::setprecision(15) << ratingPrediction;
        std::cout << std::endl;
    }

    targetsFile.close();
}

double Prediction::makePrediction(int targetUserID, int targetItemID, UserItem *useritem, CosineSimilarity *cossimilarity)
{
    double predRating = 0;
    double similaritiesSum = 0;

    std::unordered_map<int, double> similarity = cossimilarity->calculateSimilarity(useritem, targetItemID);

    std::vector<int> &itemIDs = useritem->UserItem[targetUserID];

    for (int itemID : itemIDs)
    {
        if (similarity.find(itemID) == similarity.end())
            continue;

        predRating += similarity[itemID] * (useritem->ItemUserRatings[itemID][targetUserID] - useritem->ItemAvgRating[itemID]);
        similaritiesSum += std::abs(similarity[itemID]);
    }

    if (predRating != 0 && similaritiesSum != 0)
    {
        predRating /= similaritiesSum;
        predRating += useritem->ItemAvgRating[targetItemID];

        // Exploding ratings corrections
        if (predRating > 10)
            predRating = 10;

        else if (predRating < 0)
            predRating = 0;
    }

    // If the target item is a cold-start for the target user, pick the item average rating
    else
    {
        predRating = useritem->ItemAvgRating[targetItemID];

        // If the target user is a cold-start for the target item, pick the user average rating
        if (predRating == 0)
            predRating = useritem->UserAvgRating[targetUserID];

        // Even after that, user and item is cold-start, predict the scale mean (5)
        if (predRating == 0)
            predRating = 5;
    }

    return predRating;
}
