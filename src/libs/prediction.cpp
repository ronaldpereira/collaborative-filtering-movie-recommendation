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

    std::unordered_map<int, double> similarity = cossimilarity->calculateSimilarity(useritem, targetUserID);

    std::vector<int> &userIDs = useritem->ItemUser[targetItemID];

    for (int userID : userIDs)
    {
        if (similarity.find(userID) == similarity.end())
            continue;

        predRating += similarity[userID] * (useritem->UserItemRatings[userID][targetItemID] - useritem->UserAvgRating[userID]);

        // If the target item is a cold-start for the target user, pick the average rating
        if (predRating == 0)
            predRating = useritem->UserAvgRating[targetUserID];
    }

    if (userIDs.size() != 0)
    {
        predRating /= userIDs.size() - 1;
        predRating += useritem->UserAvgRating[targetUserID];

        // Exploding ratings corrections
        if (predRating > 10)
            predRating = 10;

        else if (predRating < 0)
            predRating = 0;

        return predRating;
    }

    // If the target item is a cold-start for the target user, pick the average rating
    return useritem->UserAvgRating[targetUserID];
}
