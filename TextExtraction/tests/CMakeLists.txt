project(TextExtraction)
cmake_minimum_required (VERSION 3.10)

## testing
enable_testing()

# empty test
add_test(NAME TextExtractionNoInputPrintsUsage COMMAND TextExtraction)
set_property (TEST TextExtractionNoInputPrintsUsage PROPERTY PASS_REGULAR_EXPRESSION "Usage:")

# simple file test
add_test(NAME TextExtractionSimpleInputPrintsText COMMAND TextExtraction ${CMAKE_CURRENT_SOURCE_DIR}/Materials/HighLevelContentContext.pdf)
set_property (TEST TextExtractionSimpleInputPrintsText PROPERTY PASS_REGULAR_EXPRESSION "PathsSquares\nCirclesRectangles")
