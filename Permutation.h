#pragma once
#include "Matrix.h"
#include "Exception/ExceptionMatrix/MatrixOutOfRange.h"
#include "Exception/ExceptionMatrix/OperatorMultiplyException.h"
#include "Exception/ExceptionMatrix/InvaildSize.h"

class Permutation{
    public:
    /**
     * @brief constractor of permutation matrix
     * @param size - the size of the matrix
     */
    Permutation(const int size);

    /**
     * @brief return the size of the matrix
     */
    int Size()const;

    /**
     * @brief find where is the one on 
     * this row
     * @param row where we search the one
     */
    int FindOne(const int row) const;

    /**
     * @brief get the val of matrix in idx (i,j)
     * @param i - the row of the value
     * @param j - the col of the value
     */
    const double& operator()(const int i,const int j)const ;

    /** 
    * @brief swap the lines of the permutation matrix
    * @param row1 - the first row we switch
    * @param row2 -the second row we switch
    */
    void SwapLines(const int row1,const int row2);
    /**
     * @brief return true if p 
     * is the identity
     */
    bool isIdentity()const;

    /**
     * @brief get the derminent of the
     * matrix
     * @return double
     */
    double Det()const;

    private:
    unordered_map<int,int> changes;//the change of lines
    double det;//detrminet of the matrix
    int size;
    //the only possible value
    static constexpr double zero = 0;
    static constexpr double one = 1; 
    /**
    * @brief format the size of the matrix
    */
    string FormatSize()const;

    /**
     * @brief throw exception on case
     * we out of range of the matrix
     * @param i - the row we want access
     * @param j - the col we want access
     */
    void AccessMatrix(const int i,const int j)const;
    /**
     * @brief set the new one of the val
     * @param row - the row we change the one
     * @param oneidx - the oneidx col where
     * the one be
     */
    void SetMap(const int row,const int oneidx);
    /**
     * @brief do operator print for permutation matrix
     * @param os - the os we use
     * @param matrix - the matrix we print
     */
    friend ostream& operator<<(ostream &os,const Permutation &matrix);
};

template<class T>
/**
 * @brief do multiplication between permutation
 * matrix and regular matrix
 * @param P - the permutation matrix
 * @param matrix - the matrix we change
 */
Matrix<T> operator*(const Permutation &P,const Matrix<T> &matrix){
    if(P.Size() != matrix.GetRowSize()){
        throw OperatorMultiplyException(P.Size(),P.Size(),
        matrix.GetRowSize(),matrix.GetColSize());
    }
    if(P.isIdentity()){
        //in case which we didn't replace
        //lines
        return matrix;
    }

    unordered_map<int,set<int>>lines = 
    matrix.GetMatrixByGraph().OrderParents();
    Matrix<T> newmatrix(matrix.GetRowSize(),
    matrix.GetColSize());
    for(int i = 1; i <= P.Size(); i++){
        int newrow = P.FindOne(i);
        for(auto j : lines[newrow]){
            newmatrix(i,j,matrix(newrow,j));
        }
    }
    return newmatrix;
}