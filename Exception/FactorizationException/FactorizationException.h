#pragma once
#include <stdexcept> 
#include <string>
using namespace std;
class FactorizationException : public runtime_error{
    public:
    /**
     * @brief constractor of Factorization exception
     * @param m - the number of rows of the matrix
     * @param n - the number of cols of the matrix
     * @param msg - the msg of the error 
     */
    FactorizationException(const int m,const int n,
    const string &msg);

    //defualt desructor
    virtual ~FactorizationException() = default;
};
