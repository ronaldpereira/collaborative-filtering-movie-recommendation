#ifndef USERITEM
#define USERITEM
#include <vector>
#include <array>

class UserItem
{
private:
    std::vector<std::vector<int>> matrix;
    std::vector<int> userPosition, itemPosition;
    
public:
    void MatrixBuilder(char*);
};

#endif
