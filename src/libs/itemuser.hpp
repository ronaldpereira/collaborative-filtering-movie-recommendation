#ifndef ITEMUSER
#define ITEMUSER
#include <unordered_map>
#include <vector>

class ItemUser
{
private:
    void calculateItemsAvgRating();
    void calculateGlobalItemsAvgRating();

public:
    // Data
    std::unordered_map<int, std::unordered_map<int, int>> ItemUserRatings;
    std::unordered_map<int, std::vector<int>> UserConsumedItems;
    std::unordered_map<int, double> ItemAvgRating;
    double GlobalItemsAvg;

    // Methods
    void ItemUserRatingsBuilder(char *);
};

#endif
