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
        for(int i = 1; i <= Size();i++){
            Matrix<T>::operator()(i,i,APATHETIC);
        }
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
        Matrix<T>::operator()(row1,oneidx1row,DEFUALTVALUE);
        Matrix<T>::operator()(row2,oneidx2row,DEFUALTVALUE);
        Matrix<T>::operator()(row1,oneidx2col,APATHETIC);
        Matrix<T>::operator()(row2,oneidx1col,APATHETIC);
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