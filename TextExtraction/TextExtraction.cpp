#include "TextExtraction.h"

#include "InputFile.h"
#include "PDFParser.h"
#include "PDFWriter.h"
#include "PDFPageInput.h"

#include "./lib/interpreter/PDFRecursiveInterpreter.h"
#include "./lib/graphic-content-parsing/GraphicContentInterpreter.h"
#include "./lib/math/Transformations.h"

using namespace std;
using namespace PDFHummus;

TextExtraction::TextExtraction():textInterpeter(this) {

}
    
TextExtraction::~TextExtraction() {
    textsForPages.clear();
}

bool TextExtraction::OnParsedTextPlacementComplete(const ParsedTextPlacement& inParsedTextPlacement) {
    // filter out elements outside of the page box
    if(DoBoxesIntersect(currentPageScopeBox, inParsedTextPlacement.globalBbox))
        textsForPages.back().push_back(inParsedTextPlacement);
    return true;
}


bool TextExtraction::OnTextElementComplete(const TextElement& inTextElement) {
    return textInterpeter.OnTextElementComplete(inTextElement);
}

bool TextExtraction::OnPathPainted(const PathElement& inPathElement) {
    // IGNORE (not relevant for text extraction)
    return true;
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

        PDFPageInput pageInput(inParser,pageObject);
        PDFRectangle mediaBox = pageInput.GetMediaBox();
        currentPageScopeBox[0] = mediaBox.LowerLeftX;
        currentPageScopeBox[1] = mediaBox.LowerLeftY;
        currentPageScopeBox[2] = mediaBox.UpperRightX;
        currentPageScopeBox[3] = mediaBox.UpperRightY;

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

static const string scCRLN = "\r\n";

std::string TextExtraction::GetResultsAsText(int bidiFlag, TextComposer::ESpacing spacingFlag) {
    ParsedTextPlacementListList::iterator itPages = textsForPages.begin();
    TextComposer composer(bidiFlag, spacingFlag);

    for(; itPages != textsForPages.end();++itPages) {
        composer.ComposeText(*itPages);
        composer.AppendText(scCRLN);
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
