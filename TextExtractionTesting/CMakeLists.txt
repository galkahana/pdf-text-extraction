## testing
enable_testing()

# dummy target to make sure we got TextExtraction going
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> DEPENDS TextExtractionCLI)

# empty test
add_test(NAME TextExtractionNoInputPrintsUsage COMMAND TextExtractionCLI)
set_property (TEST TextExtractionNoInputPrintsUsage PROPERTY PASS_REGULAR_EXPRESSION "Usage:")

# simple file test
add_test(NAME TextExtractionSimpleInputPrintsText COMMAND TextExtractionCLI ${CMAKE_CURRENT_SOURCE_DIR}/Materials/HighLevelContentContext.pdf)
set_property (TEST TextExtractionSimpleInputPrintsText PROPERTY PASS_REGULAR_EXPRESSION "Paths[ \t\r\n]*Squares[ \\t\r\n]*Circles[ \t\r\n]*Rectangles")

# my cv test
add_test(NAME TextExtractionCVInputPrintsText COMMAND TextExtractionCLI ${CMAKE_CURRENT_SOURCE_DIR}/Materials/GalKahanaCV2022.pdf)
set_property (TEST TextExtractionCVInputPrintsText PROPERTY PASS_REGULAR_EXPRESSION "Curriculum Vitae")

# simple (google doc) table test
add_test(NAME TextExtractionTableInputPrintsTableData COMMAND TextExtractionCLI ${CMAKE_CURRENT_SOURCE_DIR}/Materials/test_table.pdf -t) 
set_property (TEST TextExtractionTableInputPrintsTableData PROPERTY PASS_REGULAR_EXPRESSION "\" Header 1 \",\" Header 2 \",\" Header 3 \"[\r\n]+\"[ \t]*D[ \t]*ata row 1 col 1 \",\"[ \t]*D[ \t]*ata row 1 col 2 \",\"[ \t]*D[ \t]*ata row 1 col 3 \"")

# simple (ms word) table text 
add_test(NAME TextExtractionWordTableInputPrintsTableData COMMAND TextExtractionCLI ${CMAKE_CURRENT_SOURCE_DIR}/Materials/test_table_2.pdf -t) 
set_property (TEST TextExtractionWordTableInputPrintsTableData PROPERTY PASS_REGULAR_EXPRESSION "\"Head 1 \",\"Head 2 \",\"Head 3 \",\"Head 4 \",\"Head 5 \"[\r\n]+\"Row 1 Col 1 \",\"Row 1 Col 2 \",\"Row 1 Col 3 \",\"Row 1 Col 4 \",\"Row 1 Col 5 \"")

# fuzz testing
file(GLOB fuzztestfiles ${CMAKE_CURRENT_SOURCE_DIR}/Materials/FuzzTests/*)
foreach (fuzztestfile ${fuzztestfiles})
    get_filename_component (TName ${fuzztestfile} NAME)
    add_test (NAME FuzzTest_${TName} COMMAND TextExtractionCLI ${fuzztestfile})
endforeach ()

# specifics
set_property (TEST FuzzTest_output-output-dummy.txt-34544.pdf PROPERTY PASS_REGULAR_EXPRESSION "Error: Failed to parse file")
set_property (TEST FuzzTest_radamsa-dummy-20507.pdf PROPERTY PASS_REGULAR_EXPRESSION "Error: Failed to parse file")
set_property (TEST FuzzTest_radamsa-dummy-27773.pdf PROPERTY PASS_REGULAR_EXPRESSION "Error: Failed to parse file")
set_property (TEST FuzzTest_radamsa-dummy-47574.pdf PROPERTY PASS_REGULAR_EXPRESSION "Error: Failed to parse file")

