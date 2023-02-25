add_executable(TextExtractionCLI
extract-text-cli.cpp
)

target_link_libraries (TextExtractionCLI TextExtraction::TextExtraction)
# i still want to use TextExtraction as the executable name.
set_target_properties(TextExtractionCLI PROPERTIES OUTPUT_NAME TextExtraction)

if(APPLE)
	set(CMAKE_EXE_LINKER_FLAGS "-framework CoreFoundation")
endif(APPLE)


install(TARGETS TextExtractionCLI
    EXPORT TextExtractionTargets
    RUNTIME DESTINATION bin COMPONENT executables
)