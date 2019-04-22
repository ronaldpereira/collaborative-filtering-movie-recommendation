#ifndef USERITEM
#define USERITEM
#include <unordered_map>
#include <vector>

class UserItem
{
private:
    void calculateItemsAvgRating();
    void calculateUsersAvgRating();
    void calculateGlobalItemsAvgRating();

public:
    // Data
    std::unordered_map<int, std::unordered_map<int, int>> ItemUserRatings;
    std::unordered_map<int, std::vector<int>> UserConsumedItems;
    std::unordered_map<int, double> ItemAvgRating;
    double GlobalItemsAvg;

    // Methods
    void ItemuserRatingsBuilder(char *);
};

#endif
