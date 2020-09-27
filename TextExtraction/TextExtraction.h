#pragma once

#include "EStatusCode.h"

#include "./lib/text-placements/TextPlacement.h"

#include "ErrorsAndWarnings.h"

#include <string>
#include <list>

typedef std::list<TextElementList> TextElementListList;
typedef std::list<ResultTextCommandList> ResultTextCommandListList;

class PDFParser;
class PDFDictionary;

typedef std::list<TextExtractionWarning> TextExtractionWarningList;

class TextExtraction {

    public:
        TextExtraction();
        virtual ~TextExtraction();

        PDFHummus::EStatusCode ExtractText(const std::string& inFilePath);

        TextExtractionError LatestError;
        TextExtractionWarningList LatestWarnings;  

        // end result construct
        ResultTextCommandListList textsForPages;

        // just descrypt input file to its easier to read its contnets
        PDFHummus::EStatusCode DecryptPDFForDebugging(
            const std::string& inTemplateFilePath,
            const std::string& inTargetOutputFilePath
        );

    private:
        // interim work construct
        TextElementListList textPlacementsForPages;


        PDFHummus::EStatusCode ExtractTextPlacements(PDFParser* inParser);
        PDFHummus::EStatusCode Translate(PDFParser* inParser);
        PDFHummus::EStatusCode ComputeDimensions(PDFParser* inParser);
        PDFHummus::EStatusCode ComputeResultPlacements();

        PDFDictionary* QueryFontForCommand(PDFParser* inParser, PlacedTextCommand& inCommand);

};