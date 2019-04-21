#include <cmath>
#include <unordered_map>
#include "cosinesimilarity.hpp"
#include "useritem.hpp"

CosineSimilarity::~CosineSimilarity()
{
    for (auto &sim : computedSimilarities)
        sim.second.clear();
    computedSimilarities.clear();
}

std::unordered_map<int, double> CosineSimilarity::calculateSimilarity(UserItem *useritem, int targetUserID)
{
    std::unordered_map<int, double> similarities;

    if (computedSimilarities.find(targetUserID) == computedSimilarities.end())
    {
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
    }

    else
        similarities = computedSimilarities[targetUserID];

    return similarities;
}
