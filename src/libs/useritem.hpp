#ifndef USERITEM
#define USERITEM
#include <unordered_map>
#include <vector>

class UserItem
{
private:
    void calculateUsersAvgRating();

public:
    // Data
    std::unordered_map<int, std::unordered_map<int, int>> UserItemRatings;
    std::unordered_map<int, std::vector<int>> ItemUser;
    std::unordered_map<int, double> UserAvgRating;

    // Methods
    void UserItemRatingsBuilder(char *);
    ~UserItem();
};

#endif
