#pragma once

#include "EStatusCode.h"

#include "./lib/text-parsing/ParsedTextPlacement.h"
#include "./lib/text-parsing/ITextInterpreterHandler.h"
#include "./lib/text-composition/TextComposer.h"

#include "ErrorsAndWarnings.h"

class PDFParser;

#include <sstream>
#include <string>
#include <list>

typedef std::list<ParsedTextPlacementList> ParsedTextPlacementListList;
typedef std::list<TextExtractionWarning> TextExtractionWarningList;


class TextExtraction : public ITextInterpreterHandler {

    public:
        TextExtraction();
        virtual ~TextExtraction();

        PDFHummus::EStatusCode ExtractText(const std::string& inFilePath, long inStartPage=0, long inEndPage=-1);

        TextExtractionError LatestError;
        TextExtractionWarningList LatestWarnings;  

        // end result construct
        ParsedTextPlacementListList textsForPages;

        // just descrypt input file to its easier to read its contnets
        PDFHummus::EStatusCode DecryptPDFForDebugging(
            const std::string& inTemplateFilePath,
            const std::string& inTargetOutputFilePath
        );

        std::string GetResultsAsText(int bidiFlag, TextComposer::ESpacing spacingFlag);

        // ITextInterpreterHandler implementation
        virtual bool OnParsedTextPlacementComplete(const ParsedTextPlacement& inParsedTextPlacement); 

    private:
        PDFHummus::EStatusCode ExtractTextPlacements(PDFParser* inParser, long inStartPage, long inEndPage);
};