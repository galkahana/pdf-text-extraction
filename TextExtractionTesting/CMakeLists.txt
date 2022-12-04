project(TextExtraction)
cmake_minimum_required (VERSION 3.10)

## testing
enable_testing()

# dummy target to make sure we got TextExtraction going
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS TextExtraction)

# empty test
add_test(NAME TextExtractionNoInputPrintsUsage COMMAND TextExtraction)
set_property (TEST TextExtractionNoInputPrintsUsage PROPERTY PASS_REGULAR_EXPRESSION "Usage:")

# simple file test
add_test(NAME TextExtractionSimpleInputPrintsText COMMAND TextExtraction ${CMAKE_CURRENT_SOURCE_DIR}/Materials/HighLevelContentContext.pdf)
set_property (TEST TextExtractionSimpleInputPrintsText PROPERTY PASS_REGULAR_EXPRESSION "PathsSquares\nCirclesRectangles")

# my cv test
add_test(NAME TextExtractionCVInputPrintsText COMMAND TextExtraction ${CMAKE_CURRENT_SOURCE_DIR}/Materials/GalKahanaCV2022.pdf)

# fuzz testing
file(GLOB fuzztestfiles ${CMAKE_CURRENT_SOURCE_DIR}/Materials/FuzzTests/*)
foreach (fuzztestfile ${fuzztestfiles})
    get_filename_component (TName ${fuzztestfile} NAME)
    add_test (NAME FuzzTest_${TName} COMMAND TextExtraction ${fuzztestfile})
endforeach ()

# specifics
set_property (TEST FuzzTest_output-output-dummy.txt-34544.pdf PROPERTY PASS_REGULAR_EXPRESSION "Error: Failed to parse file")
set_property (TEST FuzzTest_radamsa-dummy-20507.pdf PROPERTY PASS_REGULAR_EXPRESSION "Error: Failed to parse file")
set_property (TEST FuzzTest_radamsa-dummy-27773.pdf PROPERTY PASS_REGULAR_EXPRESSION "Error: Failed to parse file")
set_property (TEST FuzzTest_radamsa-dummy-47574.pdf PROPERTY PASS_REGULAR_EXPRESSION "Error: Failed to parse file")

