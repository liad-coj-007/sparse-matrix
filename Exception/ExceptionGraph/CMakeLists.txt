set(GRAPHEXCEPTION_SOURCES example.cpp)  # Replace with actual filenames
# Create a library from these sources
add_library(GraphExceptionLib ${GRAPHEXCEPTION_SOURCES})

target_include_directories(GraphExceptionLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})