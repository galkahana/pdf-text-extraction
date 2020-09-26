#include "TextExtraction.h"
#include "InputFile.h"
#include "PDFParser.h"

#include "./lib/interpreter/PDFRecursiveInterpreter.h"
#include "./lib/text-placements/TextPlacementsCollector.h"

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

        // now do something with the collected result.... 
    }    


    return status;
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


        // 1st phase - extract placements
        //var {pagesPlacements,formsPlacements} = extractPlacements(pdfReader,collectPlacements,readResources);
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