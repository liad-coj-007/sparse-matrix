set(SPECAILMATRIXEXCEPTION_SOURCES ExcessDenied.cpp)  # Replace with actual filenames
# Create a library from these sources
add_library(SpecailExceptionLib ${SPECAILMATRIXEXCEPTION_SOURCES})

target_include_directories(SpecailExceptionLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})