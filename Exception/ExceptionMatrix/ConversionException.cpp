#include "ConversionException.h"
using namespace std;
const string msg = "conversion faild matrix size isn't 1x1";
ConversionException::ConversionException():runtime_error(msg){} 