#pragma once
#include <stdexcept> 
#include <string>
using namespace std;

class ConversionException:public runtime_error{
    public:
    //default constractor
    ConversionException();
};