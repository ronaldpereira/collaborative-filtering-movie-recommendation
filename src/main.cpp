#include "libs/useritem.hpp"

int main(int argc, char **argv) {
    UserItem useritem(99999, 9999999);

    useritem.MatrixBuilder(argv[1]);

    return 0;
}
