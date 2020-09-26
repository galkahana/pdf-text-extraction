#include "TextExtraction.h"
#include "InputFile.h"
#include "PDFParser.h"
#include "PDFIndirectObjectReference.h"

#include "./lib/interpreter/PDFRecursiveInterpreter.h"
#include "./lib/text-placements/TextPlacementsCollector.h"
#include "./lib/font-translation/FontDecoder.h"

using namespace std;
using namespace PDFHummus;

static const string scEmpty = "";

TextExtraction::TextExtraction() {

}
    
TextExtraction::~TextExtraction() {

}

EStatusCode TextExtraction::ExtractTextPlacements(PDFParser* inParser) {
    EStatusCode status = eSuccess;

    for(unsigned long i=0;i<inParser->GetPagesCount();++i) {
        RefCountPtr<PDFDictionary> pageObject(inParser->ParsePage(i));
        PDFRecursiveInterpreter interpreter;
        TextPlacementsCollector collector;
        interpreter.InterpretPageContents(inParser, pageObject.GetPtr(), &collector);  
        PlacedTextOperationResultList& texts = collector.onDone();

        textsForPages.push_back(PlacedTextOperationResultList(texts));
    }    


    return status;
}

EStatusCode TextExtraction::Translate(PDFParser* inParser) {
    PlacedTextOperationResultListList::iterator pagesIt = textsForPages.begin();

    for(; pagesIt != textsForPages.end(); ++pagesIt) {
        PlacedTextOperationResultList::iterator resultsIt = pagesIt->begin();
        for(; resultsIt != pagesIt->end(); ++resultsIt) {
            // Determine a decoder for the text font
            RefCountPtr<PDFDictionary> fontDict;
            if(resultsIt->textState.fontRef->GetType() == PDFObject::ePDFObjectDictionary) {
                fontDict = (PDFDictionary*)resultsIt->textState.fontRef.GetPtr();
            }
            else if(resultsIt->textState.fontRef->GetType() == PDFObject::ePDFObjectIndirectObjectReference) {
                PDFObjectCastPtr<PDFDictionary> parsedFontDict(inParser->ParseNewObject(
                    ((PDFIndirectObjectReference*)resultsIt->textState.fontRef.GetPtr())->mObjectID
                ));
                if(!!parsedFontDict) {
                    fontDict = parsedFontDict.GetPtr();
                }
            }
            if(!!fontDict) {
                FontDecoder decoder(inParser, fontDict.GetPtr());
                PlacedTextRecordList::iterator recordsIt = resultsIt->text.begin();
                for(; recordsIt != resultsIt->text.end();++recordsIt) {
                    if(recordsIt->isText) {
                        // Translate the text
                        FontDecoderResult result = decoder.Translate(recordsIt->asBytes);
                        recordsIt->asText = result.asText;
                        recordsIt->translationMethod = result.translationMethod;

                        // Accumulate
                        resultsIt->allTextAsBytes.insert(resultsIt->allTextAsBytes.end(), recordsIt->asBytes.begin(), recordsIt->asBytes.end());
                        resultsIt->allTextAsText+= (result.asText.empty() ? string(" ") : result.asText);
                        resultsIt->allTextTranslationMethod = result.translationMethod;
                    }
                }
            }
        }
    }

    return eSuccess;
}


EStatusCode TextExtraction::ExtractText(const std::string& inFilePath) {
    EStatusCode status = eSuccess;
    InputFile sourceFile;

    LatestWarnings.clear();
    LatestError.code = ETextExtractionError::eErrorNone;
    LatestError.description = scEmpty;

    do {
        status = sourceFile.OpenFile(inFilePath);
        if (status != eSuccess) {
            LatestError.code = ETextExtractionError::eErrorFileNotReadable;
            LatestError.description = string("Cannot read template file ") + inFilePath;
            break;
        }


        PDFParser parser;
        status = parser.StartPDFParsing(sourceFile.GetInputStream());
        if(status != eSuccess)
        {
            LatestError.code = ETextExtractionError::eErrorInternalPDFWriter;
            LatestError.description = string("Failed to parse template file");
            break;
        }

        // 1st phase - extract text placements
        status = ExtractTextPlacements(&parser);
        if(status != eSuccess)
            break;

        // 2nd phase - translate encoded bytes to text strings.
        status = Translate(&parser);
        if(status != eSuccess)
            break;


        // 2nd phase - translate encoded bytes to text strings.
        //var state = {fontDecoders:{}};
        //translate(state,pdfReader,pagesPlacements,formsPlacements);

        // 3rd phase - compute dimensions
        //computeDimensions(state,pdfReader,pagesPlacements,formsPlacements);
        // 4th phase - flatten page placments, and simplify constructs
        //return flattenPlacements(pagesPlacements);

    } while(false);

    return status;
}