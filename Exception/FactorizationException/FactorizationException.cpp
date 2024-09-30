#include "FactorizationException.h"
#include <sstream>

using namespace std;

string FormatMessage(const int m,const int n,const string msg){
    std::ostringstream oss;
    oss << "Matrix: " << m << "x" << n << "\n";
    oss << msg << "\n";
    return oss.str();
}

FactorizationException::FactorizationException(const int m,
const int n,const string &msg):runtime_error(FormatMessage(m,n,msg)){}