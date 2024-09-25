#include "XMatrix.h"

Matrix<double> XMatrix::Identity(const int size){
    return XMatrix::Diagonal(size,size,1.0);
}

Matrix<double> XMatrix::Ones(const int m ,const int n){
    return XMatrix::FillMatrix(m,n,1.0);
}
