#include "ExcessDenied.h"
#include <sstream>  // for std::stringstream

using namespace std;

/**
 * @brief format message to the exception
 * i - the row the excess denied
 * j - the col that exceess denied
 */
string FormatMessage(const int i,const int j){
    stringstream ss;
    ss <<"Excess to the place ( " << i <<" ," << j << ") ";
    ss << "denide to safe matrix struct";
    return ss.str();
}

ExccessDenided::ExccessDenided(const int i ,const int j)
:runtime_error(FormatMessage(i,j)){}