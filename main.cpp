#include <iostream>
#include "Dict.h"
#include <ctime>

int main() {

    Dict<double, int> dict;
    uint64_t start_time =  clock();
    for (int q = 0; q < 100000000; q++)
        dict[rand()] = q;
    uint64_t end_time =  clock();
    uint64_t time = end_time-start_time;
    std::cout << time << std::endl;
    //double a = dict.getKey();
    return 0;
}
