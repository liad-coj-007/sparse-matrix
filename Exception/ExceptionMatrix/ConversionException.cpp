#include "ConversionException.h"
using namespace std;
const string msg = "conversion failed!";
ConversionException::ConversionException():runtime_error(msg){} 