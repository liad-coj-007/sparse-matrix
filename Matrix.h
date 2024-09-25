#include "Graph.h"
#include "Exception/ExceptionMatrix/MatrixOutOfRange.h"
#include "Exception/ExceptionMatrix/InvaildSize.h"
#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>
#include "Exception/ExceptionMatrix/OperatorPlusException.h"
#include "Exception/ExceptionMatrix/OperatorException.h"
#include "Exception/ExceptionMatrix/OperatorMultiplyException.h"
#include "Exception/ExceptionMatrix/ConversionException.h"


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

    template<class Function>
    /**
     * @brief constrats matrix based on function
     * @param m - number of rows
     * @param n - number of cols
     * @param accuracy - if the user want acc or ready
     * @param function - the function that
     * calc the vals of the matrix
     */
    Matrix(const int m,const int n,
     Function &function,bool accuracy = false):Matrix(m,n,accuracy){
        for(int i = 1; i <= GetRowSize();i++){
            for(int j = 1; j <= GetColSize();j++){
                this->operator()(i,j,function(i,j));
            }
        }
    }

    /**
     * @brief build 1x1 matrix
     * @param val - the val on the
     * matrix
     */
    explicit Matrix(const T &val){
        m = 1;
        n = 1;
        CalcEpsilon(false);
        this->operator()(m,n,val);
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
        if(n != other.n || m != other.m){
            throw OperatorPlusException(m,n,other.m,other.n);
        }

        for(auto it = other.data.begin();it != other.data.end();++it){
            this->operator()(it->first.from,it->first.to,
            it->second + this->operator()(it->first.from,it->first.to));
        }
        return *this;
    }

    operator T() const {
        if(m != 1 || n != 1){
            throw ConversionException();
        }  
        return this->operator()(m,n);
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

    /**
     * @brief print 
     * the sparse matrix
     * we ignore zeros 
     */
    void PrintSparse()const{
        cout << formatSize() << endl;
        for(auto it = data.begin();it != data.end();++it){
            cout << "(" << it->first.from <<", " << it->first.to;
            cout << ") = " << it->second << endl;
        }
    }
   
    /**
     * @brief get the number of rows of 
     * the matrix
     * @return int
     */
    int GetRowSize()const{return m;}

    /**
     * @brief get the number of cols of 
     * the matrix
     * @return int
     */
    int GetColSize()const{return n;}
    /**
     * @brief get the memory usage of the matrix
     * @return int 
     */
    size_t MemoryUseage() const{
        return data.memoryUseage();
    }

    /**
     * @brief set the acc of the matrix
     * @param accuracy - if we want the matrix
     * have accuracy or not
     */
    void SetAccuracy(const bool accuracy){
        CalcEpsilon(accuracy);
    }

    /**
     * @brief return sparse matrix data by graph
     * return graph referance
     */
    const Graph<int,T>& GetMatrixByGraph() const{
        return data;
    }

    template<class Iterator>
    /**
     * @brief set matrix val by a iterator
     * @param row the first row we put value
     * @param begin - the first val we add
     * @param end - the last val we didn't add him
     */
    void setIterator(int row,const Iterator &begin,
    const Iterator &end){
        pair<int,int> pos = {row,1};
        setIterator(pos,begin,end);
    }
    template<class Iterator>

     /**
     * @brief set matrix val by a iterator  on the begining
     * of the matrix
     * @param begin - the first val we add
     * @param end - the last val we didn't add him
     */
    void setIterator(const Iterator &begin,const Iterator &end){
        setIterator(1,begin,end);
    }
    template<class Iterator>
    /**
     * @brief set matrix val by a iterator
     * @param pair the first index we get to
     * @param begin - the first val we add
     * @param end - the last val we didn't add him
     */
    void setIterator(pair<int,int> pos ,Iterator begin, Iterator end){
        for(auto it = begin; it != end; ++it){
            this->operator()(pos.first,pos.second,*it);
            pos = GetNext(pos);
        }
    }

    template<typename ...Args>
    /**
     * @brief set coefficent of matrix by order
     * @param row - the row we start to change
     * @param args - the arguments we need to add
     */
    void setCoefficent(const int row,Args ...args){
        pair<int,int> pair = {row,1};
        setCoefficent(pair,args...);
    }

    template<typename ...Args>
    /**
     * @brief set coffienct of matrix by order
     * @param pos - the (row,col) we start with
     * @param value - the value we put
     * @param args - the other values
     */
    void setCoefficent(const pair<int,int> pos,const T &value,Args... args){
        T oldvalue;
        try{
            oldvalue = this->operator()(pos.first,pos.second);
             this->operator()(pos.first,pos.second,value);
             setCoefficent(GetNext(pos),args...);
        }catch(const exception &e){
            if(pos.first <= m && pos.second <= n){
                this->operator()(pos.first,pos.second,oldvalue);
            }
            throw;
        }
    }


     /**
     * @brief return -matix
     * @return matrix
     */
    Matrix<T> operator-() const{
        return -1*(*this);
    }

    /**
     * @brief return matrix multipcation
     * @param other - the other matrix we calc
     * @return matrix refernce
     */
    Matrix<T>& operator*=(const Matrix<T> &other){
        *this = (*this)*other;
         return *this;
    }

    
    /**
     * @brief return a transpose matrix
     * @return matrix
     */
    Matrix<T> operator~() const {
        Matrix<T> transpose_mat(n,m);
        for( auto it = data.begin();it != data.end();++it){
            transpose_mat(it->first.to,it->first.from,it->second);
        }
        return transpose_mat;
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
     * @brief defualt setcoefficent
     */
    void setCoefficent(const pair<int,int> pos){}

    /**
     * @brief set the pos be the next
     * entry of the matrix
     */
    pair<int,int> GetNext(const pair<int,int> &pos){
        pair<int,int> newpos = pos;
        if(newpos.second < n){
            newpos.second++;
            return newpos;
        }
        newpos.first++;
        newpos.second = 1;
        return newpos;
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
     * @param val - the val we check if he is
     * default val for the system
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

    /**
     * @brief equal to matrixs and return true if they equal
     * @param mat1 - the first matrix we equal
     * @param mat2 - the second matrix we equal
     */
    friend bool operator==(const Matrix &mat1,const Matrix &mat2){
        return mat1.GetRowSize() == mat2.GetRowSize()
        && mat1.GetColSize() == mat2.GetColSize()
        && mat1.data == mat2.data;
    }
};


template<class T>
/**
 * @brief operator + for matrix sum
 * @param mat1 - the first mat we sum
 * @param mat2 - the second mat we sum
 * @return 
 */
Matrix<T> operator+(const Matrix<T> &mat1,const Matrix<T> &mat2){
    if(mat1.MemoryUseage() <= mat2.MemoryUseage()){
        Matrix sum = mat2;
        sum += mat1;
        return sum;
    }
    Matrix sum = mat1;
    sum += mat2;
    return sum;
}

template<class T>
/**
 * @brief get exp and matrix and return exp*mat
 * @param exp - the exp we take
 * @package mat -the matrix we *
 * @return a matrix that equal mat*exp
 */
Matrix<T> operator*(const T &exp,const Matrix<T> &mat){
    Matrix<T> newmat(mat.GetRowSize(),mat.GetColSize());
    const Graph<int,T>& graph = mat.GetMatrixByGraph();
    for(auto it = graph.begin();it != graph.end();++it){
        newmat(it->first.from,it->first.to,exp*(it->second));
    }
    return newmat;
}

template<class T>
/**
 * @brief get exp and matrix and return exp*mat
 * @param exp - the exp we take
 * @package mat -the matrix we *
 * @return a matrix that equal mat*exp
 */
Matrix<T> operator*(const Matrix<T> &mat,const T &exp){
    return exp*mat;
}


template<class T>
/**
 * @brief do matrix multiplication
 * @param A - the first matrix we multiplicate
 * @param B - the second matriw we multiplicate
 * @return A*B
 */
Matrix<T> operator*(const Matrix<T> &A,const Matrix<T> &B){
    if(A.GetColSize() != B.GetRowSize()){
        throw OperatorMultiplyException(
              A.GetRowSize(),A.GetColSize(),
              B.GetRowSize(),B.GetColSize()
        );
    }
    Matrix<T> C(A.GetRowSize(),B.GetColSize(),true);
    const Graph<int,T> & ga = A.GetMatrixByGraph();
    unordered_map<int,set<int>> parentmap_b
    = B.GetMatrixByGraph().OrderParents();
    for(auto i = ga.begin(); i != ga.end(); ++i){
        for(const auto j : parentmap_b[i->first.to]){
            C(i->first.from,j,i->second *B(i->first.to,j) + 
            C(i->first.from,j));
        }
    }
    C.SetAccuracy(false);
    return C;
}

