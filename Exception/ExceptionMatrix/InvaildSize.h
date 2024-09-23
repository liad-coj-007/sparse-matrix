#pragma once
#include <stdexcept> 
#include <string>
using namespace std;

class InvaildSize : public std::invalid_argument {
    public:
        InvaildSize();

    private:
        static const std::string msg; // Declaration of the static const string
};

