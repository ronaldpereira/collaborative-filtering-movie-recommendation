#include <cmath>
#include <map>
#include <unordered_map>
#include "cosinesimilarity.hpp"
#include "useritem.hpp"

std::unordered_map<int, double> CosineSimilarity::getKNearestNeighbors(std::unordered_map<int, double> *similarities, int kNearestNeighbors)
{
    std::map<double,int> topk;
    std::unordered_map<int, double> topKSimilarities;

    for (auto &sim : *similarities)
        topk[sim.second] = sim.first;

    int i = 0;
    for (auto sim = topk.end(); sim != topk.begin() && i < kNearestNeighbors; sim--)
    {
        topKSimilarities[sim->second] = sim->first;
        i++;
    }

    return topKSimilarities;

}

std::unordered_map<int, double> CosineSimilarity::calculateSimilarity(UserItem *useritem, int targetItemID, int kNearestNeighbors)
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

            std::unordered_map<int, int> &userRatings = item.second;

            double weightedRatingSum = 0;
            double squaredRatingsUser1 = 0, squaredRatingsUser2 = 0;

            for (auto &user : target_item_ratings)
            {
                int userID = user.first;

                if (userRatings.find(userID) == userRatings.end())
                    continue;

                weightedRatingSum += (useritem->ItemUserRatings[targetItemID][userID] - useritem->ItemAvgRating[targetItemID]) * (useritem->ItemUserRatings[itemID][userID] - useritem->ItemAvgRating[itemID]);
                squaredRatingsUser1 += std::pow(useritem->ItemUserRatings[targetItemID][userID] - useritem->ItemAvgRating[targetItemID], 2);
                squaredRatingsUser2 += std::pow(useritem->ItemUserRatings[itemID][userID] - useritem->ItemAvgRating[itemID], 2);
            }

            double normalizer = std::sqrt(squaredRatingsUser1 * squaredRatingsUser2);

            if (normalizer != 0)
                similarities[itemID] = weightedRatingSum / normalizer;
        }
        // If KNN selection is active
        if (kNearestNeighbors > 0)
            similarities = getKNearestNeighbors(&similarities, kNearestNeighbors);

        // Saves the target item computed similarities for possible future use
        computedSimilarities[targetItemID] = similarities;
    }

    else
        similarities = computedSimilarities[targetItemID];

    return similarities;
}
