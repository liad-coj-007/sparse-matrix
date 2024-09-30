#pragma once
#include "FactorizationException.h"
using namespace std;

class LUException : public FactorizationException{
    public:
    LUException(const int m,const int n);
};
