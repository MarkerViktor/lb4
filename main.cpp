#include <iostream>
#include "Dict.h"


int main() {
    Dict<int, int> dict;
    for (int q = 0; q < 100; q++)
        dict[rand()%500] = q;
    int a = dict.getKey(99);
    dict.clear();
    return 0;
}
