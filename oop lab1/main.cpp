#include <iostream>
#include "include/trololo.h"

int main()
{
    std::string str;
    std::cout << "enter troll comment:";
    std::cin  >> str;

    std::cout << "result: " << trololo(str) << std::endl;

    return 0;
}