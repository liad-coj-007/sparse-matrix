#pragma once
#include "Matrix.h"
#include "LowTriangular.h"
#include "UpperTraingular.h"
#include "Permutation.h"
#include "Factorization.h"
#include <cmath> 
#include <algorithm> // For std::max
#include "Graph.h"
#include "Row.h"
#include "Exception/FactorizationException/LUException.h"
using namespace std;


template<class T>
/**
 * @brief return
 * @param num1 - the first num we equal
 * @param num2 - the second num we equal
 */
T AbsoulteMax(const T &num1 ,const T &num2){
    return max(abs(num1),abs(num2));
}



template<class T>
class LU : public Factorization<T> {
    public:
    LU(const Matrix<T>& matrix)
        : Factorization<T>(matrix, "LU"),
          U(matrix.GetRowSize()),
          P(matrix.GetColSize()),L(1){
        int n = matrix.GetColSize();
        if(n != matrix.GetRowSize()){
            throw LUException(matrix.GetRowSize(),n);
        }

        L = XMatrix::Identity<T>(n);
        Matrix<T> A = matrix;
        Factorize(A);
    }

    /**
     * @brief get the vector of soultion using 
     * lu factorization
     * @param b - the vactor we find his soultion
     */
    Vector<T> Solve(const Vector<T> &b)const{
        Vector<T> pb = P*b;
        Vector<T> y = L / pb;
        return U/y;
    }

    /**
     * @brief return const refernce of the matrix we want
     * by his name
     * @param name - the name of the matrix
     */
    const Matrix<T>& operator[](const string &arg ) const override{
        if(Lname == arg){
            return L;
        }

        if(Uname == arg){
            return U;
        }

        if(Pname == arg ){
            return P;
        }

        return Factorization<T>::operator[](arg);
    }


    private:
    static constexpr const char* Lname = "L";
    static constexpr const char* Uname = "U";
    static constexpr const char* Pname = "P";

    /**
     * @brief factorize the matrix A to lu recursively
     * @param A - the matrix we factorize
     * @param row - the number of row we factorize
     */
    void Factorize(Matrix<T> &A,const int row = FIRSTIDX){
        if(A.GetColSize() == FIRSTIDX){
            U(row,row,A(FIRSTIDX,FIRSTIDX));
            return;
        }

        set<int> first_col = A.GetMatrixByGraph().Son(FIRSTIDX);
        int pivotidx = partialPivoting(A,first_col);
        if(pivotidx != FIRSTIDX){
            A = Replace(pivotidx,row,A);
        }
        Vector<T> l1(A.GetRowSize()-1);
        Row<T> u1(A.GetColSize()-1);
        SetCol(l1,u1,A,row);
        Matrix<T> subA = BuildSubMatrix(A);
        subA  = subA + l1*u1;
        Factorize(subA,row+1); 
    }

    Matrix<T> BuildSubMatrix(const Matrix<T> &A){
        Matrix<T> submatrix(A.GetRowSize() - 1 ,A.GetColSize() -1);
        const Graph<int,T> &data = A.GetMatrixByGraph();
        for(auto it = data.begin();it != data.end(); ++it){
            if(it->first.from == FIRSTIDX || 
            it->first.to == FIRSTIDX){
                continue;
            }
            submatrix(it->first.from-1,it->first.to-1,it->second);
        }
        return submatrix;
    }
    
    void SetCol(Vector<T> &l1,Row<T> &u1,const Matrix<T> &A,
    const int row){
        U(row,row,A(FIRSTIDX,FIRSTIDX));
        set<int> firstrow = A.GetMatrixByGraph().Parent(FIRSTIDX);
        set<int> firstcol = A.GetMatrixByGraph().Son(FIRSTIDX);
        for(auto j : firstrow){
            if(j == 1){
                continue;
            }
            u1(j-1,A(FIRSTIDX,j));
            U(row,row + j -1,u1[j-1]);
        }

        for(auto j : firstcol){
            if(j == 1){continue;}
            l1(j-1,-A(j,FIRSTIDX)/A(FIRSTIDX,FIRSTIDX));
            L(row+j - 1,row,-l1[j-1]);
        }
    }

    Matrix<T> Replace(const int pivotrow, const int row,Matrix<T>& A){
        P.SwapLines(pivotrow + row -1,row);
        ReplaceL(pivotrow + row -1,row);
        if(P.Size() == A.GetRowSize()){
            return P*A;
        }
        Permutation<T> swap(A.GetRowSize());
        swap.SwapLines(pivotrow,FIRSTIDX);
       
        return swap*A;
    }


    /**
     * @brief replace L lines cordinates
     * @param pivotrow - the first row we switch
     * @param row - the second row we switch
     */
    void ReplaceL(const int pivotrow,const int row){
        for(int i = 1; i < row;i++){
            T val = L(pivotrow,i);
            L(pivotrow,i,L(row,i));
            L(row,i,val);
        }
    }


    /**
     * @brief get the first col of matrix
     * and return large pivot idx
     * @param A - the matrix we check her 
     * pivot
     * @param col - the first col on the matrix
     */
    int partialPivoting(const  Matrix<T> &A,
     const set<int> &first_col)const {
        T maxvalue = T();
        int maxrowidx = FIRSTIDX;
        for(auto j : first_col){
            if(AbsoulteMax<T>(maxvalue,A(j,FIRSTIDX)) != maxvalue){
                maxrowidx = j;
                maxvalue = A(j,FIRSTIDX);
            }
        }
        return maxrowidx;
    }

    friend ostream& operator<<(ostream &os,const LU &lu){
        os << "L = \n" << lu.L << "\n";
        os << "U = \n" << lu.U << "\n";
        os << "P = \n" << lu.P << "\n";
        return os;
    }

    LowTriangular<T> L;
    UpperTraingular<T> U;
    Permutation<T> P;
    static constexpr T ONE = T()+1; 
    static constexpr int FIRSTIDX = 1;
};

