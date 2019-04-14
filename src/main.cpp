#include <iostream>
#include <vector>
#include <memory>
#include "libs/useritem.hpp"

int main(int argc, char const *argv[])
{
    std::vector<std::shared_ptr<UserItem>> ui;
    ui.push_back(std::make_shared<UserItem>());
    std::cout << "test" << std::endl;
    
    return 0;
}
