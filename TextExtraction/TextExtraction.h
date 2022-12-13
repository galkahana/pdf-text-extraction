#pragma once

#include "EStatusCode.h"

#include "./lib/text-parsing/ParsedTextPlacement.h"
#include "./lib/text-parsing/ITextInterpreterHandler.h"
#include "./lib/text-composition/TextComposer.h"
#include "./lib/graphic-content-parsing/IGraphicContentInterpreterHandler.h"
#include "./lib/text-parsing/TextInterpreter.h"
#include  "./lib/table-line-parsing/TableLineInterpreter.h" // TMP
#include  "./lib/table-line-parsing/ITableLineInterpreterHandler.h" // TMP

#include "ErrorsAndWarnings.h"

class PDFParser;

#include <sstream>
#include <string>
#include <list>

typedef std::list<ParsedTextPlacementList> ParsedTextPlacementListList;
typedef std::list<TextExtractionWarning> TextExtractionWarningList;


class TextExtraction : public ITextInterpreterHandler, IGraphicContentInterpreterHandler, ITableLineInterpreterHandler { // TMP

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

        // IGraphicContentInterpreterHandler implementation
        virtual bool OnTextElementComplete(const TextElement& inTextElement);
        virtual bool OnPathPainted(const PathElement& inPathElement);
        virtual bool OnResourcesRead(const Resources& inResources, IInterpreterContext* inContext);

        // ITextInterpreterHandler implementation
        virtual bool OnParsedTextPlacementComplete(const ParsedTextPlacement& inParsedTextPlacement); 

        // ITableLineInterpreterHandler implementation // TMP
        virtual bool OnParsedHorizontalLinePlacementComplete(const ParsedLinePlacement& inParsedLine); 
        virtual bool OnParsedVerticalLinePlacementComplete(const ParsedLinePlacement& inParsedLine); 

    private:
        TextInterpeter textInterpeter;
        TableLineInterpreter tableLineInterpreter; // TMP

        PDFHummus::EStatusCode ExtractTextPlacements(PDFParser* inParser, long inStartPage, long inEndPage);
};