#ifndef USERITEM
#define USERITEM

class UserItem
{
private:
    int **matrix;
    int maxU, maxI;
public:
    UserItem(int, int);
    ~UserItem();
    void MatrixBuilder(char*);
};

#endif
