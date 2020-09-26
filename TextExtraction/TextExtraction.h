#pragma once

#include "EStatusCode.h"

#include "./lib/text-placements/TextPlacement.h"

#include "ErrorsAndWarnings.h"

#include <string>
#include <list>

typedef std::list<PlacedTextOperationResultList> PlacedTextOperationResultListList;

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
        PlacedTextOperationResultListList textsForPages;


        PDFHummus::EStatusCode ExtractTextPlacements(PDFParser* inParser);
        PDFHummus::EStatusCode Translate(PDFParser* inParser);

};