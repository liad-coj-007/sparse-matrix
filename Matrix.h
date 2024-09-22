#include "Graph.h"
#include "Exception/ExceptionMatrix/MatrixOutOfRange.h"
#include "Exception/ExceptionMatrix/InvaildSize.h"
#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>

template<class T>
class Matrix{
    public:
    /**
     * @brief constractor of default matrix
     * @param m - number of rows
     * @param n - number of cols
     * @param accuracy - if the user want acc or ready
     * to compromise
     */
    Matrix(const int m,const int n,bool accuracy = false){
        if(n < 0 || m < 0){
            throw InvaildSize();
        }
        this->n = n;
        this->m = m;
        CalcEpsilon(accuracy);
    }

    /**
     * @brief  that return a specific val
     * of matrix
     * @param i - the row the user want 
     * @param j - the col the user want
     * @return type refernce
     */
    const T& operator()(const int i,const int j) const {
        isAccessAble(i,j);
        if(data.ContainEdge(i,j)){
            return data(i,j);
        }
        return defaultvalue;
    }


    /**
     * @brief do operator + for two matrix
     * @param other - the other matrix we calc
     * the sum
     */
    Matrix<T>& operator+=(const Matrix<T> &other){
        
    }

    /**
     * @brief set a new value to the matrix
     * @param i - the row we want to change
     * @param j - the col we want to change
     * @param val - the val we change to
     */
    void operator()(const int i,const int j,const T &val){
        isAccessAble(i,j);
        if(isDefualtVal(val)){
            if(data.ContainEdge(i,j)){
                data.deleteEdge(i,j);
            }
            return;   
        }
        data(i,j) = val;
    }

    private:
    Graph<int,T> data;
    static constexpr T defaultvalue = T();
    int m;
    int n;
    double ep;//epsilon of data
    /**
     * @brief check if we can got to this place on the matrix
     * @param i - the row we want to get
     * @param j - the col we want to get
     */
    void isAccessAble(const int i,const int j)const {
        if(i < 1 || j < 1 || i > m || j > n){
            throw MatrixOutOfRange(i,j,m,n);
        }
    }


    /**
     * @brief calc the ep for save memory of
     * the matrix
     * @param accuracy - get from the user
     * if he want save memory or not
     */
    virtual void CalcEpsilon(bool accuracy){
        if(accuracy){
            ep = 0;
            return;
        }
        const double acc = 0.0000000001; 
        int size = n*m;
        ep = (double)size*acc;
    }

    /**
     * @brief return true if the val is on ep enviroment
     * thus we don't need to save this data
     */
    virtual bool isDefualtVal(const T &val){
        double minusep = -ep;
        return (minusep <= val && val <= ep);
    }


    /**
     * @brief format size for print
     * @return string
     */
    string formatSize()const{
        ostringstream os;
        os << m << "x" << n;
        return os.str();
    }


    /**
     * @brief print operator of matrix
     * @param os the os we use
     * @param mat - the matrix we print
     */
    friend ostream& operator<<(ostream &os,const Matrix<T> &mat){
        os << mat.formatSize() << endl;
        for (int i = 1; i <= mat.m; ++i) {
            for (int j = 1; j <= mat.n; ++j) {
                os << std::setw(10) << std::fixed << 
                std::setprecision(2) << mat(i,j);
                if (j < mat.n) {
                    os << " "; // Space between elements
                }
            }
            os << "\n"; // New line after each row
        }
        return os;
    }

};