#pragma once
#include <stdexcept> 
#include <string>
using namespace std; 

class InvaildSize:public invalid_argument{
    public:
        /**
         * @brief constractor of matrix out
         * of range
         */
        InvaildSize();
}