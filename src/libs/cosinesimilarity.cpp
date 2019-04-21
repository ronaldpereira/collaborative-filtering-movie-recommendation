#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include "cosinesimilarity.hpp"
#include "useritem.hpp"

std::unordered_map<int, double> CosineSimilarity::calculateSimilarity(UserItem *useritem, int targetUserID)
{
    std::unordered_map<int, double> similarities;
    std::unordered_map<int, int> &target_user_ratings = useritem->UserItemRatings[targetUserID];

    for (auto &user : useritem->UserItemRatings)
    {
        int userID = user.first;

        if (userID == targetUserID)
            continue;

        std::unordered_map<int, int> &item_ratings = user.second;

        double weightedRatingSum = 0;
        double squaredRatingsUser1 = 0, squaredRatingsUser2 = 0;

        for (auto &item : target_user_ratings)
        {
            int itemID = item.first;

            if (item_ratings.find(itemID) == item_ratings.end())
                continue;

            weightedRatingSum += (useritem->UserItemRatings[targetUserID][itemID] - useritem->UserAvgRating[targetUserID]) * (useritem->UserItemRatings[userID][itemID] - useritem->UserAvgRating[userID]);
            squaredRatingsUser1 += std::pow(useritem->UserItemRatings[targetUserID][itemID] - useritem->UserAvgRating[targetUserID], 2);
            squaredRatingsUser2 += std::pow(useritem->UserItemRatings[userID][itemID] - useritem->UserAvgRating[userID], 2);
        }

        double normalizer = std::sqrt(squaredRatingsUser1 * squaredRatingsUser2);

        if (normalizer != 0)
            similarities[userID] = weightedRatingSum / normalizer;
    }

    return similarities;
}

std::vector<std::vector<double>> CosineSimilarity::getTopNSimilarities(int itemPos, int n)
{
    double maxSimilarity, maxSimilarityIndex;
    std::vector<std::vector<double>> topNSimilarities;

    std::vector<double> targetItemSimilarity(itemSimilarity[itemPos].size());
    std::copy(itemSimilarity[itemPos].begin(), itemSimilarity[itemPos].end(), targetItemSimilarity.begin());

    for (int nItems = 0; nItems < n; nItems++)
    {
        maxSimilarity = -std::numeric_limits<double>::infinity();
        maxSimilarityIndex = 0;

        for (int i = 0; i < targetItemSimilarity.size(); i++)
        {
            if (targetItemSimilarity[i] > maxSimilarity && i != itemPos)
            {
                maxSimilarity = targetItemSimilarity[i];
                maxSimilarityIndex = i;
            }
        }
        topNSimilarities.push_back(std::vector<double>{maxSimilarityIndex, maxSimilarity});
        targetItemSimilarity.erase(targetItemSimilarity.begin() + maxSimilarityIndex);
    }

    return topNSimilarities;
}
