#pragma once
using namespace std;
#include "Matrix.h"  // Include Matrix header
template<class T>
class Vector:public Matrix<T>{
    public:
    /**
     * @brief vector constractor
     * @param m - the number of rows 
     * @param accuracy - if we want accuracy
     * on the vector
     */
    Vector(const int m,const bool accuracy = false):
    Matrix<T>(m,1,accuracy){}

    template<class Function>
    /**
     * @brief vector constractor
     * @param m - the number of rows 
     * @param accuracy - if we want accuracy
     * on the vector
     */
    Vector(const int m,Function &function,bool accuracy = false):
    Matrix<T>(m,1,function,accuracy){}

    /**
     * @brief get the value 
     * in the index row of the vector
     * @param row - the row the val we return
     * @return T&
     */
    const T& operator[](const int row)const {
        return Matrix<T>::operator()(row,1);
    }
    
    /**
     * @brief return the size of the vector
     * @return int
     */
    int size()const{
        return this->GetRowSize();
    }

    /**
     * @brief set a value on the vector
     * @param row - where we put the
     * new value
     * @param value - the value we put
     */
    void operator()(const int row,const T &value){
        Matrix<T>::operator()(row,1,value);
    }
};