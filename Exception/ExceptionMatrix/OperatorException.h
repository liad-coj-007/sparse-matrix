#pragma once
#include <stdexcept> 
#include <string>
using namespace std;

class OperatorException:public runtime_error{
    public:
    /**
     * @brief build a operatorException 
     * @param msg - the msg we use
     */
    explicit  OperatorException(const string &msg);
    //for desractor
    virtual ~OperatorException() = default;
};