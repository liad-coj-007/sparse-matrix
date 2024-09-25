#pragma once
using namespace std;
#include "Matrix.h"
#include <algorithm> // Required for std::min

class XMatrix{
    public:
    /**
     * @brief build a diagonal matrix
     * @param m - the number of rows
     * @param n - the number of cols
     * @param val - the val on diag
     * @return matrix
     */
    template<class T>
    static Matrix<T> Diagonal( const int m, const int n,
     const T &val){
        Matrix<T> matrix(m,n);
        int maxdiag = std::min(m,n);
        for(int i = 1; i <= maxdiag; i++){
            matrix(i,i,val);
        }
        return matrix;
     }
    /**
     * @brief build the identity matrix
     * @return matrix
     */
    static Matrix<double> Identity(const int size) ;

};