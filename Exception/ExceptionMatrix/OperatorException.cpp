#include "OperatorException.h"

OperatorException::OperatorException(const string &msg):runtime_error(msg){}