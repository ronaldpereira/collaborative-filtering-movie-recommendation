#ifndef USERITEM
#define USERITEM
#include <vector>

class UserItem
{
private:
    // Data
    std::vector<int> userLookup;
    std::vector<int> itemLookup;
    int nUser = 0;
    int nItem = 0;

    // Methods
    void insertUserItemRating(int, int, int);
    int createUser(int);
    int createItem(int);

public:
    // Data
    std::vector<std::vector<int>> matrix;

    // Methods
    void MatrixBuilder(char *);
    int getUserPosition(int);
    int getItemPosition(int);
};

#endif
