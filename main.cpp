#include <iostream>
#include "Dict.h"


int main() {
    Dict<int, std::string> dict;
    for (int q = 0; q < 100; q++)
        dict[rand()] = std::to_string(q);
    return 0;
}
