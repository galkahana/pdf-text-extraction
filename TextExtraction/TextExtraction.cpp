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
        TextElementList& texts = collector.onDone();

        textsForPages.push_back(TextElementList(texts));
    }    


    return status;
}

EStatusCode TextExtraction::Translate(PDFParser* inParser) {
    TextElementListList::iterator pagesIt = textsForPages.begin();

    for(; pagesIt != textsForPages.end(); ++pagesIt) {
        TextElementList::iterator textElementsIt = pagesIt->begin();
        for(; textElementsIt != pagesIt->end(); ++textElementsIt) {
            PlacedTextCommandList::iterator commandIt = textElementsIt->texts.begin();
            for(; commandIt != textElementsIt->texts.end(); ++commandIt) {
                // Determine a decoder for the text font
                RefCountPtr<PDFDictionary> fontDict;
                if(commandIt->textState.fontRef->GetType() == PDFObject::ePDFObjectDictionary) {
                    fontDict = (PDFDictionary*)commandIt->textState.fontRef.GetPtr();
                }
                else if(commandIt->textState.fontRef->GetType() == PDFObject::ePDFObjectIndirectObjectReference) {
                    PDFObjectCastPtr<PDFDictionary> parsedFontDict(inParser->ParseNewObject(
                        ((PDFIndirectObjectReference*)commandIt->textState.fontRef.GetPtr())->mObjectID
                    ));
                    if(!!parsedFontDict) {
                        fontDict = parsedFontDict.GetPtr();
                    }
                }
                if(!!fontDict) {
                    FontDecoder decoder(inParser, fontDict.GetPtr());
                    PlacedTextCommandArgumentList::iterator argumentIt = commandIt->text.begin();
                    for(;argumentIt != commandIt->text.end();++argumentIt) {
                        if(argumentIt->isText) {
                            // Translate the text
                            FontDecoderResult result = decoder.Translate(argumentIt->asBytes);
                            argumentIt->asText = result.asText;
                            argumentIt->translationMethod = result.translationMethod;

                            // Accumulate all args for a command
                            commandIt->allTextAsBytes.insert(commandIt->allTextAsBytes.end(), argumentIt->asBytes.begin(), argumentIt->asBytes.end());
                            commandIt->allTextAsText+= (result.asText.empty() ? string(" ") : result.asText);
                            commandIt->allTextTranslationMethod = result.translationMethod;
                        }
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

        // 3rd phase - compute dimensions
        //computeDimensions(state,pdfReader,pagesPlacements,formsPlacements);
        // 4th phase - flatten page placments, and simplify constructs
        //return flattenPlacements(pagesPlacements);

    } while(false);

    return status;
}