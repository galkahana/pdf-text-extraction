#pragma once

#include "EStatusCode.h"

#include "ErrorsAndWarnings.h"

#include <string>
#include <list>

class PDFParser;

typedef std::list<TextExtractionWarning> TextExtractionWarningList;

class TextExtraction {

    public:
        TextExtraction();
        virtual ~TextExtraction();

        PDFHummus::EStatusCode ExtractText(const std::string& inFilePath);

        TextExtractionError LatestError;
        TextExtractionWarningList LatestWarnings;  

    private:
        PDFHummus::EStatusCode ExtractTextPlacements(PDFParser* inParser);

};