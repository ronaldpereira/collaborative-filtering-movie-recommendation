#ifndef USERITEM
#define USERITEM
#include <unordered_map>
#include <vector>

class UserItem
{
private:
    void calculateItemsAvgRating();
    void calculateUsersAvgRating();

public:
    // Data
    std::unordered_map<int, std::unordered_map<int, int>> ItemUserRatings;
    std::unordered_map<int, std::unordered_map<int, int>> UserItemRatings;
    std::unordered_map<int, std::vector<int>> UserItem;
    std::unordered_map<int, double> ItemAvgRating;
    std::unordered_map<int, double> UserAvgRating;

    // Methods
    void ItemuserRatingsBuilder(char *);
    ~UserItem();
};

#endif
