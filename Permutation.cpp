#include "Permutation.h"
using namespace std;
#include <algorithm> // For std::swap


Permutation::Permutation(const int size){
    if(size <= 0){
        throw InvaildSize();
    }
    this->size = size;
    det = 1.0;
}

double Permutation::Det()const{return det;}

const double& Permutation::operator()(const int i,
const int j)const{
    AccessMatrix(i,j);
    auto it = changes.find(i);
    if (FindOne(i) == j){
        return one;
    }
    return zero;
}

void Permutation::AccessMatrix(const int i,const int j)const {
    if(i < 0 || i > size || j < 0 || j > size){
        throw MatrixOutOfRange(i,j,size,size);
    }
}

int Permutation::FindOne(const int row) const{
    AccessMatrix(row,row);
    auto it = changes.find(row);
    if(it == changes.end()){
        return row;
    }
    return it->second;
}

void Permutation::SetMap(const int row,const int oneidx){
    if(row != oneidx){
        changes[row] = oneidx;
        return;
    }
    auto it = changes.find(row);
    if(it != changes.end()){
        changes.erase(it);
    }  
}

void Permutation::SwapLines(const int row1,const int row2){
    int oneidx1 = FindOne(row1);
    int oneidx2 = FindOne(row2);
    SetMap(row1,oneidx2);
    SetMap(row2,oneidx1);
    det = -det;
}

string Permutation::FormatSize()const{
     ostringstream os;
     os << size << "x" << size;
     return os.str();
}

int Permutation::Size() const{return size;}

ostream& operator<<(ostream &os,const Permutation &matrix){
     os << matrix.FormatSize() << "\n";
     for (int i = 1; i <= matrix.size; ++i) {
        for (int j = 1; j <= matrix.size; ++j) {
            os << std::setw(10) << std::fixed << 
            std::setprecision(2) << matrix(i,j);
            if (j < matrix.size) {
                os << " "; // Space between elements
            }
        }
        os << "\n"; // New line after each row
    }
    return os;
}

bool Permutation::isIdentity()const {
    return changes.size() == 0;
}

