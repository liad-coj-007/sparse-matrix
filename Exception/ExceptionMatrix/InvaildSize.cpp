#include "InvaildSize.h"
const std::string InvaildSize::msg = "Invalid size of matrix: the rows and columns must be positive.";
InvaildSize::InvaildSize():invalid_argument(msg){}