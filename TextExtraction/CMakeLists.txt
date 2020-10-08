project(TextExtraction)
cmake_minimum_required (VERSION 3.18)


add_executable(TextExtraction 
lib/bidi/BidiConversion.cpp
lib/bidi/BidiConversion.h
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

# Start ICU deps

# k. gonna try some options here. win should have native support, and there's sometimes a package pre installed.
# if not...download and build

# try winsdk native
# i wrote this totally bymyself thank you
if(WIN32)
	include(CheckIncludeFile)
	# Win 10 SDK as internal icu support. use it, if available. there are unfortunate variants
	check_include_file(icucommon.h HAVE_ICUCOMMON)
	if(NOT HAVE_ICUCOMMON)
		check_include_file(icu.h HAVE_ICU)
	endif(NOT HAVE_ICUCOMMON)

	if(HAVE_ICUCOMMON OR HAVE_ICU)
		set(SUPPORT_ICU_BIDI 1)
		message("Found system ICU support on winsdk")
		ADD_DEFINITIONS(-DSUPPORT_ICU_BIDI=1)
		# now for minor diffs in which file is included
		if(HAVE_ICUCOMMON)
			ADD_DEFINITIONS(-DINCLUDE_ICUCOMMON)
			target_link_libraries(TextExtraction icuuc.lib icuin.lib)
		else(HAVE_ICUCOMMON) 
			ADD_DEFINITIONS(-DINCLUDE_ICU)
			target_link_libraries(TextExtraction icu.lib)			
		endif(HAVE_ICUCOMMON)
	endif(HAVE_ICUCOMMON OR HAVE_ICU)
endif(WIN32)
# try to find a pre-installed package
# got help from https://github.com/korfuri/client_cpp/blob/master/prometheus/CMakeLists.txt
if(NOT SUPPORT_ICU_BIDI)
	FIND_PACKAGE(PkgConfig)
	if(PKG_CONFIG_FOUND)
		if (APPLE)
		# Find homebrew's libicu on Mac OS although it is hidden pretty well
		set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/usr/local/opt/icu4c/lib/pkgconfig")
		endif()	
		PKG_CHECK_MODULES(ICU icu-io icu-i18n icu-uc)
		if(ICU_FOUND)
			message("Found pre-installed icu package")
			# some flags to have icu behave with C++11 or none (im just here for the C bidi funcs man...)
			ADD_DEFINITIONS(-DU_SHOW_CPLUSPLUS_API=0)
			# done tricky parts
			include_directories(${ICU_INCLUDE_DIRS})
			target_link_libraries(TextExtraction ${ICU_LDFLAGS})

			set(SUPPORT_ICU_BIDI 1)
			ADD_DEFINITIONS(-DSUPPORT_ICU_BIDI=1)
			ADD_DEFINITIONS(-DINCLUDE_UBIDI)
		endif(ICU_FOUND)
	endif(PKG_CONFIG_FOUND)
endif(NOT SUPPORT_ICU_BIDI)

# ok. still not found, let's download and build
# mostly copied from https://github.com/meta-toolkit/meta-cmake/blob/master/FindOrBuildICU.cmake
# maybe i should just include them...but they had this aweful thing
# with the failing compiler checks on darwin
if(NOT SUPPORT_ICU_BIDI AND NOT WIN32)
	include(ExternalProject)

	set(ICU_EP_PREFIX ${PROJECT_BINARY_DIR}/libIcu)
	set(ICU_EP_LIBICUDATA ${ICU_EP_PREFIX}/lib/libicudata.a)
	set(ICU_EP_LIBICUI18N ${ICU_EP_PREFIX}/lib/libicui18n.a)
	set(ICU_EP_LIBICUUC ${ICU_EP_PREFIX}/lib/libicuuc.a)
	set(ICU_EP_PATCH_COMMAND "")	
    #set(ICU_CFLAGS "-fPIC")
    #set(ICU_CXXFLAGS "-fPIC")


	ExternalProject_Add(
		libIcu
		PREFIX
        	${ICU_EP_PREFIX}
        DOWNLOAD_DIR
        	${ICU_EP_PREFIX}
        URL
        	"https://github.com/unicode-org/icu/releases/download/release-67-1/icu4c-67_1-src.tgz"
        PATCH_COMMAND
        	${ICU_EP_PATCH_COMMAND}
        CONFIGURE_COMMAND
          ${CMAKE_COMMAND} -E env
		    # Gal: i removed the following two, for some reason tests fail checking on them....
            # CC=${CMAKE_C_COMPILER}
            # CXX=${CMAKE_CXX_COMPILER}		  
            CFLAGS=${ICU_CFLAGS}
            CXXFLAGS=${ICU_CXXFLAGS}
          sh ${ICU_EP_PREFIX}/src/libIcu/source/configure
            --disable-shared --enable-static --disable-dyload --disable-extras
            --disable-tests --disable-samples --disable-icuio --with-data-packaging=static
            --prefix=<INSTALL_DIR>
		BUILD_COMMAND
        	make ${ICU_MAKE_EXTRA_FLAGS}
        INSTALL_COMMAND
        	make install
        BUILD_BYPRODUCTS
        	${ICU_EP_LIBICUDATA};${ICU_EP_LIBICUI18N};${ICU_EP_LIBICUUC}
	)

	set(ICU_INCLUDE_DIRS ${ICU_EP_PREFIX}/include)
	add_library(icudata IMPORTED STATIC)
	set_target_properties(icudata PROPERTIES IMPORTED_LOCATION
	${ICU_EP_LIBICUDATA})
	add_dependencies(icudata libIcu)

	add_library(icui18n IMPORTED STATIC)
	set_target_properties(icui18n PROPERTIES IMPORTED_LOCATION
	${ICU_EP_LIBICUI18N})
	add_dependencies(icui18n libIcu)

	add_library(icuuc IMPORTED STATIC)
	set_target_properties(icuuc PROPERTIES IMPORTED_LOCATION
	${ICU_EP_LIBICUUC})
	add_dependencies(icuuc libIcu)

	set(ICU_LIBRARIES icui18n icuuc icudata)

	message("Downloaded and built icu")	
	# some flags to have icu behave with C++11 or none (im just here for the C bidi funcs man...)
	ADD_DEFINITIONS(-DU_SHOW_CPLUSPLUS_API=0)
	# done tricky parts
	include_directories(${ICU_INCLUDE_DIRS})
	target_link_libraries(TextExtraction ${ICU_LIBRARIES})

	set(SUPPORT_ICU_BIDI 1)
	ADD_DEFINITIONS(-DSUPPORT_ICU_BIDI=1)
	ADD_DEFINITIONS(-DINCLUDE_UBIDI)

endif(NOT SUPPORT_ICU_BIDI AND NOT WIN32)

# End ICU deps

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