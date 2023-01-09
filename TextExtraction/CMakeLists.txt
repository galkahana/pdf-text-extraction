project(TextExtraction)
cmake_minimum_required (VERSION 3.10)


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
lib/graphic-content-parsing/ContentGraphicState.h
lib/graphic-content-parsing/GraphicContentInterpreter.cpp
lib/graphic-content-parsing/GraphicContentInterpreter.h
lib/graphic-content-parsing/IGraphicContentInterpreterHandler.h
lib/graphic-content-parsing/Path.h
lib/graphic-content-parsing/PathElement.h
lib/graphic-content-parsing/Resources.h
lib/graphic-content-parsing/TextElement.h
lib/graphic-content-parsing/TextGraphicState.h
lib/graphs/Graph.h
lib/graphs/Queue.h
lib/graphs/Result.h
lib/interpreter/IPDFInterpreterHandler.h
lib/interpreter/IPDFRecursiveInterpreterHandler.h
lib/interpreter/PDFInterpreter.cpp
lib/interpreter/PDFInterpreter.h
lib/interpreter/PDFRecursiveInterpreter.cpp
lib/interpreter/PDFRecursiveInterpreter.h
lib/math/Transformations.cpp
lib/math/Transformations.h
lib/pdf-writer-enhancers/Bytes.cpp
lib/pdf-writer-enhancers/Bytes.h
lib/table-csv-export/TableCSVExport.cpp
lib/table-csv-export/TableCSVExport.h
lib/table-line-parsing/ITableLineInterpreterHandler.h
lib/table-line-parsing/ParsedLinePlacement.h
lib/table-line-parsing/TableLineInterpreter.cpp
lib/table-line-parsing/TableLineInterpreter.h
lib/table-composition/Lines.h
lib/table-composition/Table.cpp
lib/table-composition/Table.h
lib/table-composition/TableComposer.cpp
lib/table-composition/TableComposer.h
lib/text-composition/TextComposer.cpp
lib/text-composition/TextComposer.h
lib/text-parsing/ITextInterpreterHandler.h
lib/text-parsing/ParsedTextPlacement.h
lib/text-parsing/TextInterpreter.cpp
lib/text-parsing/TextInterpreter.h
ErrorsAndWarnings.h
extract-text-cli.cpp
TableExtraction.cpp
TableExtraction.h
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


if(USE_BIDI)
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
	# and figured out the windows part myself. skipped mingw, you can add if you need it, or just use that cmake as is
	if(NOT SUPPORT_ICU_BIDI)
		include(ExternalProject)
		set(ICU_EP_PREFIX ${PROJECT_BINARY_DIR}/libIcu)
		set(ICU_DOWNLOAD_VERSION 67)
		set(ICU_DOWNLOAD_URL "https://github.com/unicode-org/icu/releases/download/release-${ICU_DOWNLOAD_VERSION}-1/icu4c-${ICU_DOWNLOAD_VERSION}_1-src.tgz")
		set(ICU_DOWNLOAD_HASH "SHA256=94a80cd6f251a53bd2a997f6f1b5ac6653fe791dfab66e1eb0227740fb86d5dc")

		if(MSVC)
			if(CMAKE_VS_PLATFORM_NAME STREQUAL "x64") 
				set(ICU_LIB ${ICU_EP_PREFIX}/src/libIcu/lib64)
				set(ICU_BIN ${ICU_EP_PREFIX}/src/libIcu/bin64)
			else(CMAKE_VS_PLATFORM_NAME STREQUAL "x64")
				set(ICU_LIB ${ICU_EP_PREFIX}/src/libIcu/lib)
				set(ICU_BIN ${ICU_EP_PREFIX}/src/libIcu/bin)
			endif(CMAKE_VS_PLATFORM_NAME STREQUAL "x64")

			set(ICU_INCLUDE_DIRS ${ICU_EP_PREFIX}/src/libIcu/include)
			set(ICU_EP_LIBICUUC ${ICU_LIB}/icuuc.lib)
			set(ICU_EP_LIBICUUC_DEBUG ${ICU_LIB}/icuucd.lib)
			set(ICU_EP_LIBICUIN ${ICU_LIB}/icuin.lib)
			set(ICU_EP_LIBICUIN_DEBUG ${ICU_LIB}/icuind.lib)
			set(ICU_EP_LIBICUDT ${ICU_LIB}/icudt.lib)
			set(ICU_EP_LIBICUUC_BIN ${ICU_BIN}/icuuc${ICU_DOWNLOAD_VERSION}.dll)
			set(ICU_EP_LIBICUUC_BIN_DEBUG ${ICU_BIN}/icuuc${ICU_DOWNLOAD_VERSION}d.dll)
			set(ICU_EP_LIBICUIN_BIN ${ICU_BIN}/icuin${ICU_DOWNLOAD_VERSION}.dll)
			set(ICU_EP_LIBICUIN_BIN_DEBUG ${ICU_BIN}/icuin${ICU_DOWNLOAD_VERSION}d.dll)
			set(ICU_EP_LIBICUDT_BIN ${ICU_BIN}/icudt${ICU_DOWNLOAD_VERSION}.dll)


			# to save time and avoid silly failures...specify just the targets we need for the aforementioned libs
			# ...and msbuild sln builds shared libs...so have to copy to final destination as well
			set(ICU_TARGETS /target:common /target:i18n)
			ExternalProject_Add(
						libIcu
						PREFIX
							${ICU_EP_PREFIX}
						DOWNLOAD_DIR
							${ICU_EP_PREFIX}
						URL
							${ICU_DOWNLOAD_URL}
						URL_HASH
							${ICU_DOWNLOAD_HASH}
						PATCH_COMMAND ""
						CONFIGURE_COMMAND ""
						BUILD_IN_SOURCE 1
						BUILD_COMMAND msbuild /p:Configuration=$<CONFIG> /p:Platform=${CMAKE_VS_PLATFORM_NAME} /p:SkipUWP=true <DOWNLOAD_DIR>/src/libIcu/source/allinone/allinone.sln ${ICU_TARGETS}
						COMMAND ${CMAKE_COMMAND} -E copy_directory
							${ICU_BIN}
							${PROJECT_BINARY_DIR}/$<CONFIG>
						INSTALL_COMMAND   ""
						BUILD_BYPRODUCTS ${ICU_EP_LIBICUUC};${ICU_EP_LIBICUIN};${ICU_EP_LIBICUDT};${ICU_EP_LIBICUUC_DEBUG};${ICU_EP_LIBICUIN_DEBUG}
					)

			add_library(icuuc IMPORTED SHARED)
			set_target_properties(icuuc PROPERTIES IMPORTED_IMPLIB_RELEASE
			${ICU_EP_LIBICUUC})
			set_target_properties(icuuc PROPERTIES IMPORTED_IMPLIB_DEBUG
			${ICU_EP_LIBICUUC_DEBUG})
			set_target_properties(icuuc PROPERTIES IMPORTED_LOCATION_RELEASE
			${ICU_EP_LIBICUUC_BIN})
			set_target_properties(icuuc PROPERTIES IMPORTED_LOCATION_DEBUG
			${ICU_EP_LIBICUUC_BIN_DEBUG})
			add_dependencies(icuuc libIcu)

			add_library(icuin IMPORTED SHARED)
			set_target_properties(icuin PROPERTIES IMPORTED_IMPLIB_RELEASE
			${ICU_EP_LIBICUIN})
			set_target_properties(icuin PROPERTIES IMPORTED_IMPLIB_DEBUG
			${ICU_EP_LIBICUIN_DEBUG})
			set_target_properties(icuin PROPERTIES IMPORTED_LOCATION_RELEASE
			${ICU_EP_LIBICUIN_BIN})
			set_target_properties(icuin PROPERTIES IMPORTED_LOCATION_DEBUG
			${ICU_EP_LIBICUIN_BIN_DEBUG})
			add_dependencies(icuin libIcu)

			add_library(icudt IMPORTED SHARED)
			set_target_properties(icudt PROPERTIES IMPORTED_IMPLIB
			${ICU_EP_LIBICUDT})
			set_target_properties(icudt PROPERTIES IMPORTED_LOCATION
			${ICU_EP_LIBICUDT_BIN})
			add_dependencies(icudt libIcu)		

			set(ICU_LIBRARIES icuuc icuin icudt)

			# and make sure to have the dlls in target install
			install(DIRECTORY ${ICU_BIN}/
				DESTINATION bin
				FILES_MATCHING
				PATTERN "*.dll"
			)		
		else(MSVC) # original has also support for mingw...if you want that refer to...source
			set(ICU_INCLUDE_DIRS ${ICU_EP_PREFIX}/include)
			set(ICU_EP_LIBICUDATA ${ICU_EP_PREFIX}/lib/libicudata.a)
			set(ICU_EP_LIBICUI18N ${ICU_EP_PREFIX}/lib/libicui18n.a)
			set(ICU_EP_LIBICUUC ${ICU_EP_PREFIX}/lib/libicuuc.a)

			ExternalProject_Add(
				libIcu
				PREFIX
					${ICU_EP_PREFIX}
				DOWNLOAD_DIR
					${ICU_EP_PREFIX}
				URL
					${ICU_DOWNLOAD_URL}
				URL_HASH
					${ICU_DOWNLOAD_HASH}					
				PATCH_COMMAND ""
				CONFIGURE_COMMAND
				${CMAKE_COMMAND} -E env
					# Gal: i removed the following two from darwin, for some reason tests fail checking on them....
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
		endif(MSVC)


		message("Will downloading and building icu")	
		# some flags to have icu behave with C++11 or none (im just here for the C bidi funcs man...)
		ADD_DEFINITIONS(-DU_SHOW_CPLUSPLUS_API=0)
		# done tricky parts
		include_directories(${ICU_INCLUDE_DIRS})
		target_link_libraries(TextExtraction ${ICU_LIBRARIES})

		set(SUPPORT_ICU_BIDI 1)
		ADD_DEFINITIONS(-DSUPPORT_ICU_BIDI=1)
		ADD_DEFINITIONS(-DINCLUDE_UBIDI)	
	endif(NOT SUPPORT_ICU_BIDI)

	# End ICU deps
endif(USE_BIDI)


if(SHOULD_PARSE_INTERNAL_TABLES)
	add_compile_definitions(SHOULD_PARSE_INTERNAL_TABLES)
	message (STATUS "enabling internal table parsing")
endif(SHOULD_PARSE_INTERNAL_TABLES)

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
