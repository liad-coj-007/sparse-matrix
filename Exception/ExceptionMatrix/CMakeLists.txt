set(EXCEPTIONMATRIX_SOURCES InvaildSize.cpp 
MatrixOutOfRange.cpp OperatorException.cpp 
OperatorPlusException.cpp OperatorMultiplyException.cpp
ConversionException.cpp)  # Replace with actual filenames
# Create a library from these sources
add_library(ExceptionMatrixLib ${EXCEPTIONMATRIX_SOURCES})

target_include_directories(ExceptionMatrixLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})