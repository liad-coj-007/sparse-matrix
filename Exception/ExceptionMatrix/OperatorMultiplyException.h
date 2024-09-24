#pragma once
#include <string>
using namespace std;

#include "OperatorException.h" // Adjust the path as needed

class OperatorMultiplyException:public OperatorException{
    public:
    /**
     * @brief constractor of * exception
     * @param mi - is the number of rows of the mat i
     * @param ni - is the number of rows of the mat i
     */
    OperatorMultiplyException(const int m1,const int n1,
    const int m2,const int n2); 
};