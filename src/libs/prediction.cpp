#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <unordered_map>
#include "cosinesimilarity.hpp"
#include "prediction.hpp"
#include "itemuser.hpp"

void Prediction::GetPredictions(char *targetsPath, ItemUser *itemuser, int kNearestNeighbors)
{
    int user = 0, item = 0;
    double ratingPrediction = 0;
    char *token = NULL;
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

        ratingPrediction = makePrediction(user, item, itemuser, &cossimilarity, kNearestNeighbors);

        std::cout << "u" << std::setfill('0') << std::setw(7) << user;
        std::cout << ":i" << std::setfill('0') << std::setw(7) << item;
        std::cout << "," << std::setprecision(15) << ratingPrediction;
        std::cout << std::endl;
    }

    targetsFile.close();
}

double Prediction::makePrediction(int targetUserID, int targetItemID, ItemUser *itemuser, CosineSimilarity *cossimilarity, int kNearestNeighbors)
{
    double predRating = 0;
    double similaritiesSum = 0;

    std::unordered_map<int, double> similarity = cossimilarity->calculateSimilarity(itemuser, targetItemID, kNearestNeighbors);

    std::vector<int> &itemIDs = itemuser->UserConsumedItems[targetUserID];

    for (int itemID : itemIDs)
    {
        if (similarity.find(itemID) == similarity.end())
            continue;

        predRating += similarity[itemID] * (itemuser->ItemUserRatings[itemID][targetUserID] - itemuser->ItemAvgRating[itemID]);
        similaritiesSum += std::abs(similarity[itemID]);
    }

    if (predRating != 0 && similaritiesSum != 0)
    {
        predRating /= similaritiesSum;
        predRating += itemuser->ItemAvgRating[targetItemID];

        // Exploding ratings corrections
        if (predRating > 10)
            predRating = 10;

        else if (predRating < 0)
            predRating = 0;
    }

    // If the target item doesn't have any similarity with any other item, pick the item average rating
    else
    {
        predRating = itemuser->ItemAvgRating[targetItemID];

        // If the item is a complete cold-start, uses the global items average
        if (predRating == 0)
            predRating = itemuser->GlobalItemsAvg;
    }

    return predRating;
}
