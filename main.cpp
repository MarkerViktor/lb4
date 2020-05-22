#include <iostream>
#include "Dict.h"

using namespace std;

int main() {
  Dict<int, int> dict;

    for (int q = 0; q < 10; q++)
        dict[rand() % 100] = q;

    dict.printKeysTree();
    auto a = dict.getKey(6);

    return 0;
}
