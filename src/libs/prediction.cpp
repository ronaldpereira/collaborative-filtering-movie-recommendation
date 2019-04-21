#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "cosinesimilarity.hpp"
#include "prediction.hpp"
#include "useritem.hpp"

void Prediction::GetPredictions(char *targetsPath, UserItem *useritem)
{
    int user = 0, item = 0;
    char *token = NULL;
    double ratingPrediction = 0;
    std::string line;

    CosineSimilarity cos_similarity;

    std::ifstream targetsFile;
    targetsFile.open(targetsPath);

    std::cout << "started similarities" << std::endl;
    // Pre-compute item-item similarities
    cos_similarity.PreComputeSimilarities(useritem);

    std::cout << "finished similarities" << std::endl;

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

        ratingPrediction = makePrediction(user, item, useritem, &cos_similarity);

        std::cout << "u" << std::setfill('0') << std::setw(7) << user;
        std::cout << ":i" << std::setfill('0') << std::setw(7) << item;
        std::cout << "," << std::setprecision(15) << ratingPrediction;
        std::cout << std::endl;
    }

    // user = 39;
    // item = 60196;

    // std::cout << "started pred" << std::endl;

    // ratingPrediction = makePrediction(user, item, useritem, &cos_similarity);

    // std::cout << "u" << std::setfill('0') << std::setw(7) << user;
    // std::cout << ":i" << std::setfill('0') << std::setw(7) << item;
    // std::cout << "," << std::setprecision(15) << ratingPrediction;
    // std::cout << "finished pred" << std::endl;

    targetsFile.close();
}

double Prediction::makePrediction(int userID, int itemID, UserItem *useritem, CosineSimilarity *cos_similarity)
{
    int itemPos = useritem->getItemPosition(itemID);

    if (itemPos >= 0)
    {
        // k = Total similarity neighbors
        int k = 30;
        std::vector<std::vector<double>> topNSimilarities = cos_similarity->getTopNSimilarities(itemPos, k);
            
        double accumulatedRating = 0;
        int itemIndex = 0;

        for (int i = 0; i < k; i++)
        {
            itemIndex = int(topNSimilarities[i][0]);
            accumulatedRating += double(topNSimilarities[i][1]) * double(useritem->matrix[userID][itemIndex]);
        }

        return double(accumulatedRating) / k;
    }

    return 0;
}
