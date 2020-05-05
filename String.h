//
// Created by marker on 02.03.2020.
//

#ifndef LB2_STRING_H
#define LB2_STRING_H

#include <string>
#include <vector>

class String : public std::string {
public:
    std::vector<String> split(std::string str);

    String strip();

    String format(const int &);

    String format(const String &);

    String format(const double &);

    String(const char *string) : std::string(string) {};

    String() : std::string("") {};
};

#endif //LB2_STRING_H
