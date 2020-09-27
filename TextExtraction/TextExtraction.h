#pragma once

#include "EStatusCode.h"

#include "ObjectsBasicTypes.h"

#include "./lib/text-placements/TextPlacement.h"

#include "ErrorsAndWarnings.h"
#include "RefCountPtr.h"

#include <string>
#include <list>

typedef std::list<TextElementList> TextElementListList;
typedef std::list<ResultTextCommandList> ResultTextCommandListList;

class PDFObject;
class PDFParser;
class PDFDictionary;
class FontDecoder;

struct LessRefCountPDFObject {
    bool operator()( const RefCountPtr<PDFObject>& lhs, const RefCountPtr<PDFObject>& rhs ) const {
        return lhs.GetPtr() < rhs.GetPtr();
    }
};  

typedef std::list<TextExtractionWarning> TextExtractionWarningList;

typedef std::map<ObjectIDType, FontDecoder> ObjectIDTypeToFontDecoderMap;
typedef std::map< RefCountPtr<PDFObject>, FontDecoder,  LessRefCountPDFObject> PDFObjectToFontDecoderMap;

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

        std::string GetResultsAsText();

    private:
        // interim work construct
        TextElementListList textPlacementsForPages;

        // font decoders caches
        ObjectIDTypeToFontDecoderMap refrencedFontDecoderCache;
        PDFObjectToFontDecoderMap embeddedFontDecoderCache;


        PDFHummus::EStatusCode ExtractTextPlacements(PDFParser* inParser);
        PDFHummus::EStatusCode Translate(PDFParser* inParser);
        PDFHummus::EStatusCode ComputeDimensions(PDFParser* inParser);
        PDFHummus::EStatusCode ComputeResultPlacements();

        FontDecoder* GetDecoderForCommand(PDFParser* inParser, PlacedTextCommand& inCommand);

};