#pragma once
#include <stdexcept> 
#include <string>
using namespace std;

class OperatorException:public runtime_error{
    public:
    /**
     * @brief build a operatorException 
     * @param msg - the msg we use
     * @param mi - the number of rows
     * of the matrix i
     * @param ni - the number of cols of
     * the matrix i
     */
    OperatorException(const int m1,const int n1,
    const int m2,const int n2,const string &msg);
    //for desractor
    virtual ~OperatorException() = default;
};