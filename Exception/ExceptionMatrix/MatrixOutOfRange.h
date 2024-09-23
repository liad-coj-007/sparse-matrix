#pragma once
#include <stdexcept> 
#include <string>
using namespace std;

class MatrixOutOfRange:public runtime_error{
    public:
        /**
         * @brief constractor of matrix out
         * of range
         * @param i - the i the user take
         * @param j - the j  the user take
         * @param m - the number of rows of the matrix
         * @param n - the numebr of cols of the matrix
         */
        MatrixOutOfRange(const int i,const int j,
        const int m,const int n);
};