#include <math.h>
#include <vector>
#include "operations.hpp"
#include "useritem.hpp"

void CosineSimilarity::PreComputeSimilarities(UserItem *useritem)
{
    std::vector<int> item1Vec, item2Vec;

    for (int i = 0; i < useritem->nItem; i++)
    {
        for (int j = 0; j < useritem->nUser; j++)
            item1Vec.push_back(useritem->matrix[j][i]);

        itemSimilarity.push_back(std::vector<int>(0));

        for (int k = i+1; k < useritem->nItem; k++) {
            for (int l = 0; l < useritem->nUser; l++)
                item2Vec.push_back(useritem->matrix[l][k]);

            itemSimilarity[i].push_back(calculateSimilarity(item1Vec, item2Vec));
        }
    }
}

double CosineSimilarity::calculateSimilarity(std::vector<int> item1, std::vector<int> item2){
    double ratingsProdSum = 0, ratingsSquaredSumItem1 = 0, ratingsSquaredSumItem2 = 0;
    double similarity = 0;
    for (int i = 0; i < item1.size(); i++) {
        ratingsProdSum += item1[i] + item2[i];
        ratingsSquaredSumItem1 += std::pow(double(item1[i]), 2);
        ratingsSquaredSumItem2 += std::pow(double(item2[i]), 2);
    }
    similarity = ratingsProdSum / (std::sqrt(ratingsSquaredSumItem1) + std::sqrt(ratingsSquaredSumItem2));
}
