#include <cmath>
#include <unordered_map>
#include "cosinesimilarity.hpp"
#include "useritem.hpp"

std::unordered_map<int, double> CosineSimilarity::calculateSimilarity(UserItem *useritem, int targetItemID)
{
    std::unordered_map<int, double> similarities;

    if (computedSimilarities.find(targetItemID) == computedSimilarities.end())
    {
        std::unordered_map<int, int> &target_item_ratings = useritem->ItemUserRatings[targetItemID];

        for (auto &item : useritem->ItemUserRatings)
        {
            int itemID = item.first;

            if (itemID == targetItemID)
                continue;

            std::unordered_map<int, int> &user_ratings = item.second;

            double weightedRatingSum = 0;
            double squaredRatingsUser1 = 0, squaredRatingsUser2 = 0;

            for (auto &user : target_item_ratings)
            {
                int userID = user.first;

                if (user_ratings.find(userID) == user_ratings.end())
                    continue;

                weightedRatingSum += (useritem->ItemUserRatings[targetItemID][userID] - useritem->ItemAvgRating[targetItemID]) * (useritem->ItemUserRatings[itemID][userID] - useritem->ItemAvgRating[itemID]);
                squaredRatingsUser1 += std::pow(useritem->ItemUserRatings[targetItemID][userID] - useritem->ItemAvgRating[targetItemID], 2);
                squaredRatingsUser2 += std::pow(useritem->ItemUserRatings[itemID][userID] - useritem->ItemAvgRating[itemID], 2);
            }

            double normalizer = std::sqrt(squaredRatingsUser1 * squaredRatingsUser2);

            if (normalizer != 0)
                similarities[itemID] = weightedRatingSum / normalizer;
        }
    }

    else
        similarities = computedSimilarities[targetItemID];

    return similarities;
}
