#pragma once
#include "Matrix.h"
#include <stdexcept>

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
     * @param arg
     * the name of the matrix
     */
    virtual const Matrix<T>& operator[](const string &arg) const{
        throw invalid_argument("The arg isn't exsit on this system");
    }
    virtual ~Factorization() = default;
    private:
    string factorname;
};