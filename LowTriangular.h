#pragma once
using namespace std;
#include "Matrix.h"  // Include Matrix header
#include "Vector.h"
#include "Exception/SpecailMatrixException/ExcessDenied.h"
#include "Exception/ExceptionMatrix/NoSoultion.h"
template<class T>
class LowTriangular:public Matrix<T>{
    public:
    /**
     * @brief constractor of default matrix
     * @param n - number of cols & rows
     * @param accuracy - if the user want acc or ready
     * to compromise
     */
    LowTriangular(const int n,const bool accuracy = false):
    Matrix<T>(n,n,accuracy){}

    /**
     * @brief set a new value to the matrix
     * @param i - the row we want to change
     * @param j - the col we want to change
     * @param val - the val we change to
     */
    void operator()(const int i,const int j,const T &value) override{
        if(i < j){
            throw ExccessDenided(i,j);
        }
        Matrix<T>::operator()(i,j,value);
    }

   /**
     * @brief  that return a specific val
     * of matrix
     * @param i - the row the user want 
     * @param j - the col the user want
     * @return type refernce
     */
    const T& operator()(const int i,const int j)const{
        return Matrix<T>::operator()(i,j);
    }
};

template <class T>
/**
 * @brief solve Ax = b
 * @param A - the matrix we solve for
 * @param b - the vector we want to equal to
 * @return vector x that represent the solution
 */
Vector<T> operator/(const LowTriangular<T> &A,const Vector<T> &b){
    T defaultval = T();
    Vector<T> x(A.GetColSize());
    unordered_map<int,set<int>> parentmap = 
    A.GetMatrixByGraph().OrderParents();
    for(int i = 1; i <= A.GetRowSize();i++){
        T cordinate = b[i]; 
        for(auto j : parentmap[i]){
            if(i != j){
                cordinate -= x[j]*A(i,j);
            }
        }

        if(cordinate == defaultval){
            //because it sparse vector
            continue;
        }else if(A(i,i) == defaultval){
            throw NoSoultion();
        }else{
            x(i, cordinate / A(i, i));
        }
    }
    return x;
}

