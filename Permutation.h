#pragma once
#include "Matrix.h"
#include "Exception/ExceptionMatrix/MatrixOutOfRange.h"
#include "Exception/ExceptionMatrix/OperatorMultiplyException.h"
#include "Exception/SpecailMatrixException/ExcessDenied.h" // Corrected spelling

template<class T>
class Permutation : public Matrix<T> { // Added 'public' inheritance
    public:
    /**
     * @brief Constructor of permutation matrix
     * @param size - the size of the matrix
     */
    Permutation(const int size,bool accuracy = false) : Matrix<T>(size, 
    size,accuracy) {
        det = APATHETIC;
        for(int i = 1; i <= Size();i++){
            Matrix<T>::operator()(i,i,APATHETIC);
        }
    }

    /**
     * @brief Return the size of the matrix
     */
    int Size() const {
        return Matrix<T>::GetRowSize();
    }

    /**
     * @brief set a new value to the matrix
     * @param i - the row we want to change
     * @param j - the col we want to change
     * @param val - the val we change to
     * delete set function
     */
    void operator()(const int i,const int j,const T &val)override{
        isAccessAble(i,j);
        
        throw ExccessDenided(i,j);
    }
    
    /**
     * @brief swap the lines of the permutation matrix
     * @param row1 - the first row we switch
     * @param row2 - the second row we switch
     */
    void SwapLines(const int row1,const int row2){
        isAccessAble(row1,row1);
        isAccessAble(row2,row2);
        unordered_map<int,set<int>> colsmap = 
        Matrix<T>::GetMatrixByGraph().OrderParents();
        int col1 = colsmap[row1].begin().operator*();
        int col2 = colsmap[row2].begin().operator*();
        Matrix<T>::operator()(row1,col1,DEFUALTVALUE);
        Matrix<T>::operator()(row2,col2,DEFUALTVALUE);
        Matrix<T>::operator()(row1,col2,APATHETIC);
        Matrix<T>::operator()(row2,col1,APATHETIC);
    }

    /**
     * @brief return the detrminet of matrix
     */
    T Det()const {
        return det;
    }

    private:
    T det;//derminent of the matrix
    static constexpr T DEFUALTVALUE = T();
    static constexpr T APATHETIC = T() + 1;

    /**
     * @brief check if we can got to this place on the matrix
     * @param i - the row we want to get
     * @param j - the col we want to get
     */
    void isAccessAble(const int i,const int j)const {
        if(i < 1 || j < 1 || i > Size() || j > Size()){
            throw MatrixOutOfRange(i,j,Size(),Size());
        }
    }

};