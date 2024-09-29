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
    Permutation(const int size) : Matrix<T>(size, size) {
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
    int FindApathetic(const int row) const {
        AccessMatrix(row, row);
        auto it = changes.find(row);
        return (it == changes.end()) ? row : it->second;
    }

    /**
     * @brief Get the value of the matrix at (i,j)
     * @param i - the row of the value
     * @param j - the col of the value
     */
    const T& operator()(const int i,const int j)const override{
        auto it = changes.find(i);
        if(FindApathetic(i) == j){
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
        int oneidx1 = FindApathetic(row1);
        int oneidx2 = FindApathetic(row2);
        SetMap(row1, oneidx2);
        SetMap(row2, oneidx1);
        det = -det;
    }

    /**
     * @brief Return true if this is the identity matrix
     */
    bool isIdentity() const {
        return changes.empty();
    }

    /**
     * @brief Get the determinant of the matrix
     * @return double
     */
    T Det() const {
        return det;
    }

    void print() const {
        Matrix<T>::print();
    }

private:
    std::unordered_map<int, int> changes; // The change of lines
    T det; // Determinant of the matrix
    static constexpr T DEFUALTVALUE = T();
    static constexpr double APATHETIC = T() + 1;

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
    void SetMap(const int row, const int oneidx) {
        if (row != oneidx) {
            changes[row] = oneidx;
            return;
        }
        changes.erase(row); // Simplified
    }
};

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
        int newrow = P.FindApathetic(i);
        for(auto j : lines[newrow]){
            newmatrix(i,j,matrix(newrow,j));
        }
    }
    return newmatrix;
}