#include "OperatorPlusException.h"
#include <sstream> // Include for std::ostringstream


string FormatMessage(const int m1,const int n1,
    const int m2,const int n2){
    std::ostringstream oss;
    oss << "Matrix 1: " << m1 << "x" << n1 << "\n";
    oss << "Matrix 2: " << m2 << "x" << n2 << "\n";
    oss << "Error: Matrices cannot be added (dimensions must match).\n";
    return oss.str();
}


OperatorPlusException::OperatorPlusException(const int m1,const int n1,
    const int m2,const int n2):OperatorException(FormatMessage(m1,n1,m2,n2)){}

