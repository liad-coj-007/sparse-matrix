#pragma once
using namespace std;
#include "Matrix.h"
#include <algorithm> // Required for std::min
#include "Exception/ExceptionMatrix/InverseFailed.h"



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

    template<class T>
    /**
     * @brief return the inverse matrix of the matrix
     * @param matrix - the matrix we search her inverse
     * 
     */
    static Matrix<T> Inv(const Matrix<T> &matrix){
        if(matrix.GetRowSize() != matrix.GetColSize()){
            throw InverseFailed();
        }

        LU lu(matrix);
        Matrix<T> inv(matrix.GetRowSize(),matrix.GetColSize());
        try{
            for(int i = 1; i <= matrix.GetColSize();i++){
                Graph<int,T> ci = lu.Solve(
                    XMatrix::e<T>(i,matrix.GetColSize())).GetMatrixByGraph();
                for(auto it = ci.begin();it != ci.end();++it){
                    inv(it->first.from,i,it->second);
                }
            }
        }catch(const exception &e){
            throw InverseFailed();
        }
        return inv;
    }
    

    template<class T>
    /**
     * @brief return a vector ei 
     * @param idx - when we put the apathtic
     * @param size - the size of the vector
     */
    static Vector<T> e(const int idx,const int size){
        const T apathtic = T()+1;
        Vector<T> ei(size);
        ei(idx,apathtic);
        return ei;
    }

    template<class T>
    /**
     * @brief fill matrix with specific value
     * @param m - number of rows
     * @param n - number of cols
     * @param value - the value we fill with
     */
    static Matrix<T> FillMatrix(const int m,const int n,const T &value){
        auto function = [value](const int i,
        const int j){return value;};
        Matrix<T> matrix(m,n,function);
        return matrix;
    }

    /**
     * @brief return of matrix fill by ones
     * @param m - the number of rows
     * @param n - number of cols
     * 
     */
    static Matrix<double> Ones(const int m ,const int n);

    template<class T,typename ...Args>
    /**
     * @brief set the diagonal from the start of the matrix
     * @param matrix - the matrix we want to change
     * @param args - the values we want to put in
     * the matrix
     */
    static void Diagonal(Matrix<T> &matrix,Args ...args){
        Diagonal(1,matrix,args...);
    }

    template<class T,typename ...Args>
    /**
     * @brief set the daigonal of the matrix
     * @param row - the row we start to change the
     * diagonal
     * @param matrix - the matrix we change
     * @param value - the value we put 
     * on the matrix 
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

    template<class T>
    /**
     * @brief build the identity matrix
     * @return matrix
     */
    static Matrix<T> Identity(const int size){
        return XMatrix::Diagonal<T>(size,size,T()+1);
    }
    
    private:
    template<class T,typename ...Args>
    /**
     * @brief default diagonal set
     * don't do nothing
     * @param row - the row we change
     * @param matrix the matrix we change
     */
    static void Diagonal(int row,Matrix<T> &matrix){}

};