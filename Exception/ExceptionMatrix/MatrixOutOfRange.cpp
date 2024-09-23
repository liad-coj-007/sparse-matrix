#include "MatrixOutOfRange.h"
#include <sstream>  // for std::stringstream

string formatMessage(const int i,const int j,const int m,
const int n){
     std::stringstream ss;
     ss << "Matrix out of range: "
       << "attempted access at (" << i << ", " << j << "), "
       << "but the matrix size is " << m << "x" << n;
    return ss.str();
}

MatrixOutOfRange::MatrixOutOfRange(const int i,const int j,
        const int m,const int n):runtime_error(formatMessage(i,j,m,n)){}
        
