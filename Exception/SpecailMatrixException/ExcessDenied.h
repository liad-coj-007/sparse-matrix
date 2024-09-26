#pragma once
#include <stdexcept> 
#include <string>

using namespace std;

class ExccessDenided :public runtime_error{
    public:
    /**
     * @brief constractore
     * @param i - the row that acess denied
     * @param j - the col that acess denied
     */
    ExccessDenided(const int i,const int j);
};