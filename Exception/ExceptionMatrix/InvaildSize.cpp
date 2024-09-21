#include "InvaildSize.h"
const string msg = "matrix out of range the rows and cols need to be positive";
InvaildSize::InvaildSize():invalid_argument(msg){}