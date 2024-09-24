#include "OperatorException.h"

#include <sstream> // Include for std::ostringstream

/**
 * @brief fromat message for operator
 * plus exception
 * @param mi -the number of rows of matrix i
 * @param ni - the number of cols of matrix i
 * @param msg - the error msg
 */
string FormatMessage(const int m1,const int n1,
    const int m2,const int n2,const string &msg){
    std::ostringstream oss;
    oss << "Matrix 1: " << m1 << "x" << n1 << "\n";
    oss << "Matrix 2: " << m2 << "x" << n2 << "\n";
    oss << msg << "\n";
    return oss.str();
}

OperatorException::OperatorException(const int m1,const int n1,
    const int m2,const int n2,const string &msg):
    runtime_error(FormatMessage(m1,n1,m2,n2,msg)){}