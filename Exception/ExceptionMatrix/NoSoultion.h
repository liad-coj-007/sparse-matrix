#pragma once
#include <stdexcept> 
#include <string>
using namespace std;

class NoSoultion: public runtime_error{
    public:
    //defualt constractor
    NoSoultion();
};