#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>
#include <vector>
#include "cosinesimilarity.hpp"
#include "useritem.hpp"

void CosineSimilarity::PreComputeSimilarities(UserItem *useritem)
{
    std::vector<int> item1Vec, item2Vec;

    for (int i = 0; i < useritem->nItem; i++)
    {
        std::cout << "\nitem1: " << i << std::endl;
        itemSimilarity.push_back(std::vector<double>(0));

        item1Vec.clear();
        for (int j = 0; j < useritem->nUser; j++)
            item1Vec.push_back(useritem->matrix[j][i]);

        for (int k = 0; k < useritem->nItem; k++)
        {
            std::cout << "\ritem2: " << k << std::flush;
            // If k < i, the similarity between this two items has already been calculated
            if (k < i)
                itemSimilarity[i].push_back(itemSimilarity[k][i]);

            // If k == i, they are the same items, so similarity is maximum
            else if (k == i)
                itemSimilarity[i].push_back(1);

            // If k > i, the simillarity has not been calculated yet
            else
            {
                item2Vec.clear();
                for (int l = 0; l < useritem->nUser; l++)
                    item2Vec.push_back(useritem->matrix[l][k]);

                itemSimilarity[i].push_back(calculateSimilarity(item1Vec, item2Vec));
            }
        }
    }
}

double CosineSimilarity::calculateSimilarity(std::vector<int> item1, std::vector<int> item2)
{
    double ratingsProdSum = 0, ratingsSquaredSumItem1 = 0, ratingsSquaredSumItem2 = 0;
    double similarity = 0;    

    for (int i = 0; i < item1.size(); i++)
    {
        ratingsProdSum += double(item1[i]) * double(item2[i]);
        ratingsSquaredSumItem1 += std::pow(double(item1[i]), 2);
        ratingsSquaredSumItem2 += std::pow(double(item2[i]), 2);
    }

    similarity = double(ratingsProdSum) / (std::sqrt(ratingsSquaredSumItem1) * std::sqrt(ratingsSquaredSumItem2));

    return similarity;
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
