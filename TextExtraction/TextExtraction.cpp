#include "TextExtraction.h"

#include "InputFile.h"
#include "PDFParser.h"
#include "PDFWriter.h"


#include "./lib/interpreter/PDFRecursiveInterpreter.h"
#include "./lib/graphic-content-parsing/GraphicContentInterpreter.h"

using namespace std;
using namespace PDFHummus;

TextExtraction::TextExtraction():
    textInterpeter(this), 
    tableLineInterpreter(this)  // TMP
{

}
    
TextExtraction::~TextExtraction() {
    textsForPages.clear();
}

bool TextExtraction::OnParsedHorizontalLinePlacementComplete(const ParsedLinePlacement& inParsedLine) { // TMP
    return true;
}

bool TextExtraction::OnParsedVerticalLinePlacementComplete(const ParsedLinePlacement& inParsedLine) { // TMP
    return true;
}


bool TextExtraction::OnParsedTextPlacementComplete(const ParsedTextPlacement& inParsedTextPlacement) {
    textsForPages.back().push_back(inParsedTextPlacement);
    return true;
}


bool TextExtraction::OnTextElementComplete(const TextElement& inTextElement) {
    return textInterpeter.OnTextElementComplete(inTextElement);
}

bool TextExtraction::OnPathPainted(const PathElement& inPathElement) {
    return tableLineInterpreter.OnPathPainted(inPathElement);
}

bool TextExtraction::OnResourcesRead(const Resources& inResources, IInterpreterContext* inContext) {
    return textInterpeter.OnResourcesRead(inResources, inContext);
}

EStatusCode TextExtraction::ExtractTextPlacements(PDFParser* inParser, long inStartPage, long inEndPage) {
    EStatusCode status = eSuccess;
    unsigned long start = (unsigned long)(inStartPage >= 0 ? inStartPage : (inParser->GetPagesCount() + inStartPage));
    unsigned long end = (unsigned long)(inEndPage >= 0 ? inEndPage :  (inParser->GetPagesCount() + inEndPage));
    GraphicContentInterpreter interpreter;


    if(end > inParser->GetPagesCount()-1)
        end = inParser->GetPagesCount()-1;
    if(start > end)
        start = end;

    for(unsigned long i=start;i<=end && status == eSuccess;++i) {
        RefCountPtr<PDFDictionary> pageObject(inParser->ParsePage(i));
        if(!pageObject) {
            status = eFailure;
            break;
        }
        textsForPages.push_back(ParsedTextPlacementList());
        // the interpreter will trigger the textInterpreter which in turn will trigger this object to collect text elements
        interpreter.InterpretPageContents(inParser, pageObject.GetPtr(), this);  
    }    

    textInterpeter.ResetInterpretationState();

    return status;
}

static const string scEmpty = "";

EStatusCode TextExtraction::ExtractText(const std::string& inFilePath, long inStartPage, long inEndPage) {
    EStatusCode status = eSuccess;
    InputFile sourceFile;

    LatestWarnings.clear();
    LatestError.code = eErrorNone;
    LatestError.description = scEmpty;

    textsForPages.clear();

    do {
        status = sourceFile.OpenFile(inFilePath);
        if (status != eSuccess) {
            LatestError.code = eErrorFileNotReadable;
            LatestError.description = string("Cannot read file ") + inFilePath;
            break;
        }


        PDFParser parser;
        status = parser.StartPDFParsing(sourceFile.GetInputStream());
        if(status != eSuccess)
        {
            LatestError.code = eErrorInternalPDFWriter;
            LatestError.description = string("Failed to parse file");
            break;
        }

        status = ExtractTextPlacements(&parser, inStartPage, inEndPage);
        if(status != eSuccess)
            break;

    } while(false);

    return status;
}


std::string TextExtraction::GetResultsAsText(int bidiFlag, TextComposer::ESpacing spacingFlag) {
    ParsedTextPlacementListList::iterator itPages = textsForPages.begin();
    TextComposer composer(bidiFlag, spacingFlag);

    for(; itPages != textsForPages.end();++itPages) {
        composer.ComposeText(*itPages);
    }

    return composer.GetText();
}


EStatusCode TextExtraction::DecryptPDFForDebugging(
    const string& inTemplateFilePath,
    const string& inTargetOutputFilePath
) {
    return PDFWriter::RecryptPDF(  
		inTemplateFilePath,
		"",
		inTargetOutputFilePath,
		LogConfiguration::DefaultLogConfiguration(),
		PDFCreationSettings(false, true)
    );
}
