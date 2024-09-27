#pragma once
#include <stdexcept> 
#include <string>
#include "../Vector.h"
#include "../Matrix.h"
#include <iomanip>  // For std::setprecision and std::fixed

using namespace std;

template<class T>
class NoSoultion: public runtime_error{
    public:
    NoSoultion(const Matrix<T> &A,const Vector<T> &b) :
    runtime_error(FormatMessage(A,b)){}

    private:
    /**
     * @brief format a message no soultion
     * @param A - the matrix in the equation
     * @param b - the vector we equal with
     */
    string FormatMessage(const Matrix<T> &A,const Vector<T> &b){
        ostringstream oss;
        oss << "No Soultion Found!\n";
        if(A.GetColSize() != b.GetRowSize()){
            oss << "the size don't correct";
            return oss.str();
        }

        for (int i = 1; i <= A.GetRowSize(); ++i) {
            for (int j = 1; j <= A.GetColSize(); ++j) {
                if(j != 1){
                    oss << std::setw(10); 
                }
                oss << std::fixed << std::setprecision(2) 
                << A(i,j) << " ";
            }
            oss << std::setw(5) << "x" << i << " ";

            oss << "| " << std::fixed << 
            std::setprecision(2) << b[i] << "\n"; 
        }
        return oss.str();
    }

};