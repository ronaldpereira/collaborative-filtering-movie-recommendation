#ifndef USERITEM
#define USERITEM
#include <vector>

class UserItem
{
private:
    // Data
    int nUser = 0;
    int nItem = 0;

    // Methods
    void insertUserItemRating(int, int, int);
    int getUserPosition(int);
    int getItemPosition(int);
    int createUser(int);
    int createItem(int);

public:
    // Data
    std::vector<std::vector<int>> matrix;
    std::vector<int> userLookup;
    std::vector<int> itemLookup;

    // Methods
    void MatrixBuilder(char*);
};

#endif
