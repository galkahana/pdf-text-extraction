project(TextExtraction)
cmake_minimum_required (VERSION 3.10)

# sillyness i should handle better sometime from within pdfwriter
if(CMAKE_GENERATOR STREQUAL "Xcode")
    set(IS_XCODE TRUE)
endif(CMAKE_GENERATOR STREQUAL "Xcode")


ADD_SUBDIRECTORY(LibAesgm)
ADD_SUBDIRECTORY(LibJpeg)
ADD_SUBDIRECTORY(ZLib)
ADD_SUBDIRECTORY(LibTiff)
ADD_SUBDIRECTORY(FreeType)
ADD_SUBDIRECTORY(LibPng)
ADD_SUBDIRECTORY(PDFWriter)
ADD_SUBDIRECTORY(TextExtraction)

enable_testing()
ADD_SUBDIRECTORY(TextExtractionTesting)
