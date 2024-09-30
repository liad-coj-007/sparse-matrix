#pragma once
#include "Matrix.h"
#include "Exception/ExceptionMatrix/MatrixOutOfRange.h"
#include "Exception/ExceptionMatrix/OperatorMultiplyException.h"
#include "Exception/SpecailMatrixException/ExcessDenied.h" // Corrected spelling

template<class T>
class Permutation : public Matrix<T> { // Added 'public' inheritance
public:
    /**
     * @brief Constructor of permutation matrix
     * @param size - the size of the matrix
     */
    Permutation(const int size,bool accuracy = false) : Matrix<T>(size, 
    size,accuracy) {
        det = APATHETIC;
    }

    /**
     * @brief Return the size of the matrix
     */
    int Size() const {
        return Matrix<T>::GetRowSize();
    }

    /**
     * @brief Find where the one is on this row
     * @param row - where we search for the one
     */
    int FindApatheticByRow(const int row) const {
        AccessMatrix(row, row);
        auto it = changesrow.find(row);
        return (it == changesrow.end()) ? row : it->second;
    }

    /**
     * @brief Find where the one is on this col
     * @param col - where we search for the one
     */
    int FindApatheticByCol(const int col)const {
        AccessMatrix(col, col);
        auto it = changescol.find(col);
        return (it == changescol.end()) ? col :it->second;
    }

    /**
     * @brief Get the value of the matrix at (i,j)
     * @param i - the row of the value
     * @param j - the col of the value
     */
    const T& operator()(const int i,const int j)const override{
        auto it = changesrow.find(i);
        if(FindApatheticByRow(i) == j){
            return APATHETIC;
        }
        return DEFUALTVALUE;
    }

    /**
     * @brief Set a new value to the matrix
     * @param i - the row we want to change
     * @param j - the col we want to change
     * @param val - the value we change to
     */
    void operator()(const int i, const int j, const T& value) override {
        throw ExccessDenided(i, j); // Fixed spelling
    }

    /** 
    * @brief Swap the lines of the permutation matrix
    * @param row1 - the first row we switch
    * @param row2 - the second row we switch
    */
    void SwapLines(const int row1, const int row2) {
        int oneidx1row = FindApatheticByRow(row1);
        int oneidx2row = FindApatheticByRow(row2);
        SetMapRow(row1, oneidx2row);
        SetMapRow(row2, oneidx1row);
        int oneidx1col = FindApatheticByCol(oneidx1row);
        int oneidx2col = FindApatheticByCol(oneidx2row);
        SetMapByCol(oneidx1row,oneidx2col);
        SetMapByCol(oneidx2row,oneidx1col);
        det = -det;
    }


    /**
     * @brief Return true if this is the identity matrix
     */
    bool isIdentity() const {
        return changesrow.empty();
    }

    /**
     * @brief Get the determinant of the matrix
     * @return double
     */
    T Det() const {
        return det;
    }

    /**
     * @brief return a transpose matrix
     * @return matrix
     */
    Matrix<T> operator~() const override{
        Matrix<T> matrix = *this;
        return ~matrix;
    }



    /**
     * @brief return sparse matrix data by graph
     * return graph referance
     */
    Graph<int,T> GetMatrixByGraph() const override{
        Matrix<T> matrix = *this;
        return matrix.GetMatrixByGraph();
    }

    /**
     * @brief get the memory usage of the matrix
     * @return int 
     */
    size_t MemoryUseage()const override{
        size_t total = 0;
        total += sizeof(changesrow) + sizeof(changescol);
        total += changesrow.size() * sizeof(pair<int,int>);
        total += changescol.size() * sizeof(pair<int,int>);
        return total;
    }

    private:
    std::unordered_map<int, int> changesrow; // The change of lines
    std::unordered_map<int,int> changescol;
    T det; // Determinant of the matrix
    static constexpr T DEFUALTVALUE = T();
    static constexpr T APATHETIC = T() + 1;

    /**
     * @brief Throw exception if we are out of range of the matrix
     * @param i - the row we want to access
     * @param j - the col we want to access
     */
    void AccessMatrix(const int i, const int j) const {
        if (i < 0 || i > Size() || j < 0 || j > Size()) { // Fixed bounds check
            throw MatrixOutOfRange(i, j, Size(), Size());
        }
    }

    /**
     * @brief Set the new one in the value map
     * @param row - the row we change the one
     * @param oneidx - the index of the column where the one is
     */
    void SetMapRow(const int row, const int oneidx) {
        if (row != oneidx) {
            changesrow[row] = oneidx;
            return;
        }
        changesrow.erase(row); // Simplified
    }

    void SetMapByCol(const int col,const int oneidx){
        if(col != oneidx){
            changescol[col] = oneidx;
            return;
        }
        changescol.erase(col);
    }

};


template < class T>
/**
 * @brief do operator + for matrix
 * @param matrix - the matrix we take
 * @param P - permutation matrix
 */
Matrix<T> operator+(const Matrix<T> &matrix,const Permutation<T> &P){
    Matrix<T> A = P;
    return A + matrix;
}

template < class T>
/**
 * @brief do operator + for matrix
 * @param matrix - the matrix we take
 * @param P - permutation matrix
 */
Matrix<T> operator+(const Permutation<T> &P,const Matrix<T> &matrix){
    return matrix + P;
}

template < class T>
/**
 * @brief do operator + for matrix
 * @param P1 - the first matrix we take
 * @param P2 - the second matrix we take
 */
Matrix<T> operator+(const Permutation<T> &P1, const Permutation<T> &P2){
    Matrix<T> A = P1;
    return A + P2;
}

template<class T>
/**
 * @brief do multiplication between permutation
 * matrix and regular matrix
 * @param P - the permutation matrix
 * @param matrix - the matrix we change
 */
Matrix<T> operator*(const Permutation<T> &P,const Matrix<T> &matrix){
    if(P.Size() != matrix.GetRowSize()){
        throw OperatorMultiplyException(P.Size(),P.Size(),
        matrix.GetRowSize(),matrix.GetColSize());
    }
    if(P.isIdentity()){
        //in case which we didn't replace
        //lines
        return matrix;
    }

    unordered_map<int,set<int>>lines = 
    matrix.GetMatrixByGraph().OrderParents();
    Matrix<T> newmatrix(matrix.GetRowSize(),
    matrix.GetColSize());
    for(int i = 1; i <= P.Size(); i++){
        int newrow = P.FindApatheticByRow(i);
        for(auto j : lines[newrow]){
            newmatrix(i,j,matrix(newrow,j));
        }
    }
    return newmatrix;
}

template<class T>
/**
 * @brief do multiplication between permutation
 * matrix and regular matrix
 * @param P - the permutation matrix
 * @param matrix - the matrix we change
 */
Matrix<T> operator*(const Matrix<T> &matrix,
const Permutation<T> &P){
    if(P.Size() != matrix.GetColSize()){
        throw OperatorMultiplyException(P.Size(),P.Size(),
        matrix.GetRowSize(),matrix.GetColSize());
    }

    if(P.isIdentity()){
        //in case which we didn't replace
        //lines
        return matrix;
    }
    unordered_map<int,set<int>> cols = matrix.GetMatrixByGraph().OrderSons();
    Matrix<T> newmatrix(matrix.GetRowSize(),
    matrix.GetColSize());
    for(int j = 1; j <= P.Size(); j++){
        int oneidx = P.FindApatheticByCol(j);
        for(auto i : cols[oneidx]){
            newmatrix(i,j,matrix(i,oneidx));
        }
    }
    return newmatrix;
}

template<class T>
/**
 * @brief do multiplication between permutation
 * matrix and regular matrix
 * @param P1 - the permutation matrix
 * @param P2 - the matrix we change
 */
Matrix<T> operator*(const Permutation<T> &P1,
const Permutation<T> &P2){
   Matrix<T> A = P1;
   Matrix<T> B = P2;
   return A*B;
}