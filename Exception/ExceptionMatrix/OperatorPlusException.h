#pragma once
#include <string>

#include "OperatorException.h" // Adjust the path as needed


class OperatorPlusException:public OperatorException {
    public:
    /**
     * @brief constractor of plus exception
     * @param mi - is the number of rows of the mat i
     * @param ni - is the number of rows of the mat i
     */
    OperatorPlusException(const int m1,const int n1,
    const int m2,const int n2);
};