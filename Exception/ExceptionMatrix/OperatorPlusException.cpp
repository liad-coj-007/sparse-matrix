#include "OperatorPlusException.h"
const string msg = "Error the size of the matrixs must be equal!";
OperatorPlusException::OperatorPlusException(const int m1,const int n1,
    const int m2,const int n2):OperatorException(m1,n1,m2,n2,msg){}

