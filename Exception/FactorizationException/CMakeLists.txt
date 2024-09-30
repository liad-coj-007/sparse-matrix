set(FACTORIZATION_SOURCES FactorizationException.cpp
LUException.cpp)  # Replace with actual filenames
# Create a library from these sources
add_library(FactorizationExceptionLib ${FACTORIZATION_SOURCES})

target_include_directories(FactorizationExceptionLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})