cmake_minimum_required (VERSION 3.15)
project(TextExtraction VERSION 1.1.4)

# options
option(USE_BIDI  "should support bi-directional text")
option(SHOULD_PARSE_INTERNAL_TABLES  "should table parsing read internal tables")


# hummus dependency
include(FetchContent)
FetchContent_Declare(
  PDFHummus
  URL https://github.com/galkahana/PDF-Writer/archive/refs/tags/v4.6.2.tar.gz
  URL_HASH SHA256=0a36815ccc9d207028567f90039785c824b211169ba5da68de84d0c15455ab62
  DOWNLOAD_EXTRACT_TIMESTAMP FALSE
  FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(PDFHummus)

# local code
ADD_SUBDIRECTORY(TextExtraction)
ADD_SUBDIRECTORY(TextExtractionCLI)

if(PROJECT_IS_TOP_LEVEL AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/TextExtractionTesting)
    # avoid installing the testing materials altogether when included in another project.
    # it's annoying when in parent all, and more annoying to then get the tests added
    # to the parent project ctest.
    enable_testing()
    ADD_SUBDIRECTORY(TextExtractionTesting)
  endif()


# cpack
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${TextExtraction_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${TextExtraction_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_GENERATOR "ZIP")
include(CPack)

# package install
install(EXPORT TextExtractionTargets
  FILE TextExtractionTargets.cmake
  DESTINATION lib/cmake/TextExtraction
  NAMESPACE TextExtraction::
)

include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/TextExtractionConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/TextExtraction"
  )

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/TextExtractionConfigVersion.cmake"
    VERSION "${TextExtraction_VERSION_MAJOR}.${TextExtraction_VERSION_MINOR}"
    COMPATIBILITY AnyNewerVersion
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/TextExtractionConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/TextExtractionConfigVersion.cmake
  DESTINATION lib/cmake/TextExtraction
  )

export(EXPORT TextExtractionTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/TextExtractionTargets.cmake"
  NAMESPACE TextExtraction::
)