#pragma once
#include "Matrix.h"

template<class T>
class Row : public Matrix<T>{
    public:
     /**
     * @brief row constractor
     * @param n - the number of cols 
     * @param accuracy - if we want accuracy
     * on the row
     */
    Row(const int n,
    const bool accuracy = false):
    Matrix<T>(1,n,accuracy){}
    /**
     * @brief row constractor
     * @param n - the number of cols 
     * @param accuracy - if we want accuracy
     * on the row
     * @param function - the function that 
     * return a val of specfic cordinate
     */
    template<class Function>
    Row(const int n,Function &function,
    const bool accuracy = false):
    Matrix<T>(1,n,function,accuracy){}

    /**
     * @brief get the value 
     * in the index col of the row
     * @param col - the col the val we return
     * @return T&
     */
    virtual const T& operator[](const int col)const {
        return Matrix<T>::operator()(1,col);
    }

    /**
     * @brief return the size of the row
     * @return int
     */
    virtual int size()const{
        return this->GetColSize();
    }

     /**
     * @brief set a value on the row
     * @param col - where we put the
     * new value
     * @param value - the value we put
     */
    virtual void operator()(const int col,
    const T &value){
        Matrix<T>::operator()(1,col,value);
    }


};