project(TextExtraction)
cmake_minimum_required (VERSION 2.6)


add_executable(TextExtraction 
lib/font-translation/Encoding.cpp
lib/font-translation/Encoding.h
lib/font-translation/FontDecoder.cpp
lib/font-translation/FontDecoder.h
lib/font-translation/StandardFontsDimensions.cpp
lib/font-translation/StandardFontsDimensions.h
lib/font-translation/Translation.h
lib/interpreter/IPDFInterpreterHandler.h
lib/interpreter/IPDFRecursiveInterpreterHandler.h
lib/interpreter/PDFInterpreter.cpp
lib/interpreter/PDFInterpreter.h
lib/pdf-writer-enhancers/Bytes.cpp
lib/pdf-writer-enhancers/Bytes.h
lib/interpreter/PDFRecursiveInterpreter.cpp
lib/interpreter/PDFRecursiveInterpreter.h
lib/text-placements/TextPlacement.h
lib/text-placements/TextPlacementsCollector.cpp
lib/text-placements/TextPlacementsCollector.h
lib/text-placements/TPCollectionState.cpp
lib/text-placements/TPCollectionState.h
lib/text-placements/Transformations.cpp
lib/text-placements/Transformations.h
ErrorsAndWarnings.h
extract-text-cli.cpp
TextExtraction.cpp
TextExtraction.h
)

if(PDFHUMMUS_NO_DCT)
	add_definitions(-DPDFHUMMUS_NO_DCT=1)
endif(PDFHUMMUS_NO_DCT)

if(PDFHUMMUS_NO_TIFF)
	add_definitions(-DPDFHUMMUS_NO_TIFF=1)
endif(PDFHUMMUS_NO_TIFF)

if(PDFHUMMUS_NO_PNG)
	add_definitions(-DPDFHUMMUS_NO_PNG=1)
endif(PDFHUMMUS_NO_PNG)

include_directories (${PDFWriter_SOURCE_DIR})
include_directories (${LIBAESGM_INCLUDE_DIRS})
include_directories (${ZLIB_INCLUDE_DIRS})
if(NOT PDFHUMMUS_NO_DCT)
	include_directories (${LIBJPEG_INCLUDE_DIRS})
else(NOT PDFHUMMUS_NO_DCT)
	add_definitions(-DPDFHUMMUS_NO_DCT=1)
endif(NOT PDFHUMMUS_NO_DCT)

if(NOT PDFHUMMUS_NO_TIFF)
	include_directories (${LIBTIFF_INCLUDE_DIRS})
else(NOT PDFHUMMUS_NO_TIFF)
	add_definitions(-DPDFHUMMUS_NO_TIFF=1)
endif(NOT PDFHUMMUS_NO_TIFF)
include_directories (${FREETYPE_INCLUDE_DIRS})

if(NOT PDFHUMMUS_NO_PNG)
	include_directories (${LIBPNG_INCLUDE_DIRS})
else(NOT PDFHUMMUS_NO_PNG)
	add_definitions(-DPDFHUMMUS_NO_PNG=1)
endif(NOT PDFHUMMUS_NO_PNG)

add_dependencies(TextExtraction PDFWriter) #add_dependencies makes sure that dependencies are built before main target

target_link_libraries (TextExtraction PDFWriter)
target_link_libraries (TextExtraction ${LIBAESGM_LDFLAGS})
target_link_libraries (TextExtraction ${FREETYPE_LDFLAGS})
if(NOT PDFHUMMUS_NO_DCT)
	target_link_libraries (TextExtraction ${LIBJPEG_LDFLAGS})
endif(NOT PDFHUMMUS_NO_DCT)
target_link_libraries (TextExtraction ${ZLIB_LDFLAGS})
if(NOT PDFHUMMUS_NO_TIFF)
	target_link_libraries (TextExtraction ${LIBTIFF_LDFLAGS})
endif(NOT PDFHUMMUS_NO_TIFF)
if(NOT PDFHUMMUS_NO_PNG)
	target_link_libraries (TextExtraction ${LIBPNG_LDFLAGS})
endif(NOT PDFHUMMUS_NO_PNG)

if(APPLE)
	set(CMAKE_EXE_LINKER_FLAGS "-framework CoreFoundation")
endif(APPLE)


install(TARGETS TextExtraction
    RUNTIME DESTINATION bin COMPONENT executable
)