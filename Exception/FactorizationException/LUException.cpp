#include "LUException.h"
using namespace std;
const string msg = "the matrix isn't squre";
LUException::LUException(const int m,const int n):
FactorizationException(m,n,msg){}
