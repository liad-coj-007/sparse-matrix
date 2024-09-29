#pragma once
#include "Matrix.h"

template<class T>
class Factorization{
    public:
    /**
    * @brief factor the matrix to parts 
    * @param matrix - the matrix we compose
    * @param factorname - the name of the factorization
    * we use
    */
    Factorization(const Matrix<T> &matrix,
    const string &factorname = ""){
        this->factorname = factorname;
    }

    /**
     * @brief return the factorize name
     * @return string of the name
     */
    string getFactorize()const{return factorname;}
    /**
     * @brief return const refernce of the matrix we want
     * by his name
     * @param name - the name of the matrix
     */
    virtual const Matrix<T> GetMatrix(const string &name) = 0;
    private:
    string factorname;
};