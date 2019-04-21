#ifndef USERITEM
#define USERITEM
#include <unordered_map>
#include <vector>

class UserItem
{
private:
    void calculateItemsAvgRating();

public:
    // Data
    std::unordered_map<int, std::unordered_map<int, int>> ItemUserRatings;
    std::unordered_map<int, std::vector<int>> UserItem;
    std::unordered_map<int, double> ItemAvgRating;

    // Methods
    void ItemuserRatingsBuilder(char *);
    ~UserItem();
};

#endif
