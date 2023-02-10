cmake_minimum_required (VERSION 3.25)
project(TextExtraction)

# sillyness i should handle better sometime from within pdfwriter
if(CMAKE_GENERATOR STREQUAL "Xcode")
    set(IS_XCODE TRUE)
endif(CMAKE_GENERATOR STREQUAL "Xcode")


ADD_SUBDIRECTORY(TextExtraction)

enable_testing()
ADD_SUBDIRECTORY(TextExtractionTesting)
