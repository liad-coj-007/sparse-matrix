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
    template<class T,typename ...Args>
    static void Diagonal(Matrix<T> &matrix,Args ...args){
        Diagonal(1,matrix,args...);
    }
    template<class T,typename ...Args>
    /**
     * @brief set the daigonal of the matrix
     * @param row - the row we start to change the
     * diagonal
     * @param matrix - the matrix we change
     * @ 
     */
    static void Diagonal(const int row ,Matrix<T> &matrix,const T &value,
    Args ... args){
        T oldval;
        try{
            oldval = matrix(row,row);
            matrix(row,row,value);
            Diagonal(row+1,matrix,args...);
        }catch(const exception &e){
            if(row <= matrix.GetRowSize() &&
             row <= matrix.GetColSize()){
                matrix(row,row,oldval);
             }
            throw;
        }
    }

    /**
     * @brief build the identity matrix
     * @return matrix
     */
    static Matrix<double> Identity(const int size) ;
    private:
    template<class T,typename ...Args>
    static void Diagonal(int row,Matrix<T> &matrix){}

};