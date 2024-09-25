#include "XMatrix.h"


Matrix<double> XMatrix::Identity(const int size){
    return XMatrix::Diagonal(size,size,1.0);
}