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

            itemSimilarity[i].push_back(calculateSimilarity(&item1Vec, &item2Vec));
        }
    }
}

double CosineSimilarity::calculateSimilarity(std::vector<int> *item1, std::vector<int> *item2){
    return 0;
}
