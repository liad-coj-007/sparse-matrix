#pragma once
#include "Matrix.h"
#include "LowTriangular.h"
#include "UpperTraingular.h"
#include "Permutation.h"
#include "Factorization.h"
#include "XMatrix.h"
#include <cmath> 
#include <algorithm> // For std::max
#include "Graph.h"
using namespace std;



template<class T>
/**
 * @brief return
 * @param num1 - the first num we equal
 * @param num2 - the second num we equal
 */
const T& AbsoulteMax(const T &num1 ,const T &num2){
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
            //TODO: throw exception
        }

        L = XMatrix::Identity<T>(n);
        Matrix<T> A = matrix;
        Factorize(A);
    }

    const Matrix<T> GetMatrix(const string &name)override{
        return L * U;
    }


    private:
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
        Matrix<T> pivotmatrix(1,1);
        if(pivotidx != FIRSTIDX){
            A = Replace(pivotidx,row,A);
        }
        Vector<T> l1(A.GetColSize()-1);
        Vector<T> u1(A.GetRowSize()-1);
        SetCol(l1,u1,A,row);
        Matrix<T> subA = BuildSubMatrix(A);
        subA  = subA + l1*(~u1);
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

    


    void SetCol(Vector<T> &l1,Vector<T> &u1,const Matrix<T> &A,
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
        if(P.Size() == A.GetRowSize()){
            return P*A;
        }
        Permutation<T> swap(A.GetRowSize());
        swap.SwapLines(pivotrow,FIRSTIDX);
        return swap*A;
    }

    /**
     * @brief get the first col of matrix
     * and return large pivot idx
     * @param A - the matrix we check her 
     * pivot
     * @param col - the first col on the matrix
     */
    int partialPivoting(const Matrix<T> &A,
    const set<int> &first_col)const {
        T maxvalue = A(FIRSTIDX,FIRSTIDX);
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

