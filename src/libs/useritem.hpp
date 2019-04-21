#ifndef USERITEM
#define USERITEM
#include <unordered_map>

class UserItem
{
public:
    // Data
    std::unordered_map<int, std::unordered_map<int, int>> uiratings;

    // Methods
    void UserItemRatingsBuilder(char *);
    ~UserItem();
};

#endif
