#include "OperatorMultiplyException.h"
using namespace std;
const string msg = "Error: the number of cols of matrix 1 don't equal to number of rows of matrix 2!";

OperatorMultiplyException::OperatorMultiplyException(
    const int m1,const int n1,const int m2,const int n2
):OperatorException(m1,n1,m2,n2,msg){}