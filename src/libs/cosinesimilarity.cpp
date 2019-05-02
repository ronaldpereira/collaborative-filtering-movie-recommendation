#include <iostream>

#include <cmath>
#include <algorithm>
#include <map>
#include <unordered_map>
#include "cosinesimilarity.hpp"
#include "itemuser.hpp"

std::unordered_map<int, double> CosineSimilarity::getKNearestNeighbors(std::unordered_map<int, double> *similarities, int kNearestNeighbors)
{
    std::vector<std::pair<int, double>> simVector(kNearestNeighbors);
    std::unordered_map<int, double> topKSimilarities;

    std::partial_sort_copy(similarities->begin(), similarities->end(),
                           simVector.begin(), simVector.end(),
                           [](const std::pair<int, double> &a,
                              const std::pair<int, double> &b) {
                               return a.second > b.second;
                           });

    for (auto &sim : simVector)
        topKSimilarities[sim.first] = sim.second;

    return topKSimilarities;
}

std::unordered_map<int, double> CosineSimilarity::calculateSimilarity(ItemUser *itemuser, int targetItemID, int kNearestNeighbors)
{
    std::unordered_map<int, double> similarities;

    if (computedSimilarities.find(targetItemID) == computedSimilarities.end())
    {
        std::unordered_map<int, int> &targetItemRatings = itemuser->ItemUserRatings[targetItemID];

        for (auto &item : itemuser->ItemUserRatings)
        {
            int itemID = item.first;

            if (itemID == targetItemID)
                continue;

            std::unordered_map<int, int> &userRatings = item.second;

            double weightedRatingSum = 0;
            double squaredRatingsUser1 = 0, squaredRatingsUser2 = 0;

            for (auto &user : targetItemRatings)
            {
                int userID = user.first;

                if (userRatings.find(userID) == userRatings.end())
                    continue;

                weightedRatingSum += (itemuser->ItemUserRatings[targetItemID][userID] - itemuser->ItemAvgRating[targetItemID]) * (itemuser->ItemUserRatings[itemID][userID] - itemuser->ItemAvgRating[itemID]);
                squaredRatingsUser1 += std::pow(itemuser->ItemUserRatings[targetItemID][userID] - itemuser->ItemAvgRating[targetItemID], 2);
                squaredRatingsUser2 += std::pow(itemuser->ItemUserRatings[itemID][userID] - itemuser->ItemAvgRating[itemID], 2);
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
