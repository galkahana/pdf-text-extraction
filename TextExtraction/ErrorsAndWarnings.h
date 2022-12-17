#pragma once

#include <string>

enum EExtractionWarning {
    eWarningNone = 0, // null, means no warning
};

enum EExtractionError {
    eErrorNone = 0, // null means no error
    eErrorFileNotReadable = 301,
    eErrorInternalPDFWriter = 302
};


struct ExtractionError {
    EExtractionError code;
    std::string description;
};

struct ExtractionWarning {
    EExtractionWarning code;
    std::string description;
};