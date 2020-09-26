#pragma once

#include <string>

enum ETextExtractionWarning {
    eWarningNone = 0, // null, means no warning
};

enum ETextExtractionError {
    eErrorNone = 0, // null means no error
    eErrorFileNotReadable = 301,
    eErrorInternalPDFWriter = 302
};


struct TextExtractionError {
    ETextExtractionError code;
    std::string description;
};

struct TextExtractionWarning {
    ETextExtractionWarning code;
    std::string description;
};