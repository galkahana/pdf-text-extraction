#include "TableExtraction.h"

#include "InputFile.h"
#include "PDFParser.h"
#include "PDFWriter.h"
#include "PDFPageInput.h"


#include "./lib/interpreter/PDFRecursiveInterpreter.h"
#include "./lib/graphic-content-parsing/GraphicContentInterpreter.h"
#include "./lib/table-csv-export/TableCSVExport.h"
#include "./lib/table-composition/TableComposer.h"



using namespace std;
using namespace PDFHummus;


TableExtraction::TableExtraction():
    textInterpeter(this), 
    tableLineInterpreter(this)
{

}
    
TableExtraction::~TableExtraction() {
    textsForPages.clear();
    tableLinesForPages.clear();
    tablesForPages.clear();
    mediaBoxesForPages.clear();
}

bool TableExtraction::OnParsedHorizontalLinePlacementComplete(const ParsedLinePlacement& inParsedLine) {
    tableLinesForPages.back().horizontalLines.push_back(inParsedLine);
    return true;
}

bool TableExtraction::OnParsedVerticalLinePlacementComplete(const ParsedLinePlacement& inParsedLine) {
    tableLinesForPages.back().verticalLines.push_back(inParsedLine);
    return true;
}


bool TableExtraction::OnParsedTextPlacementComplete(const ParsedTextPlacement& inParsedTextPlacement) {
    textsForPages.back().push_back(inParsedTextPlacement);
    return true;
}


bool TableExtraction::OnTextElementComplete(const TextElement& inTextElement) {
    return textInterpeter.OnTextElementComplete(inTextElement);
}

bool TableExtraction::OnPathPainted(const PathElement& inPathElement) {
    return tableLineInterpreter.OnPathPainted(inPathElement);
}

bool TableExtraction::OnResourcesRead(const Resources& inResources, IInterpreterContext* inContext) {
    return textInterpeter.OnResourcesRead(inResources, inContext);
}

EStatusCode TableExtraction::ExtractTablePlacements(PDFParser* inParser, long inStartPage, long inEndPage) {
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

        mediaBoxesForPages.push_back(pageInput.GetMediaBox());
        textsForPages.push_back(ParsedTextPlacementList());
        tableLinesForPages.push_back(Lines());
        // the interpreter will trigger the textInterpreter which in turn will trigger this object to collect text elements
        interpreter.InterpretPageContents(inParser, pageObject.GetPtr(), this);  
    }    

    textInterpeter.ResetInterpretationState();

    return status;
}

static const string scEmpty = "";

void TableExtraction::ClearState() {
    textsForPages.clear();
    tableLinesForPages.clear();
    tablesForPages.clear();
    mediaBoxesForPages.clear();
    LatestWarnings.clear();
    LatestError.code = eErrorNone;
    LatestError.description = scEmpty;
}

EStatusCode TableExtraction::ExtractTables(const std::string& inFilePath, long inStartPage, long inEndPage) {
    EStatusCode status = eSuccess;
    InputFile sourceFile;

    ClearState();

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

        status = ExtractTablePlacements(&parser, inStartPage, inEndPage);
        if(status != eSuccess)
            break;

        ComposeTables();
    } while(false);

    return status;
}

PDFHummus::EStatusCode TableExtraction::ExtractTables(PDFParser* inParser, long inStartPage, long inEndPage) {
    ClearState();

    PDFHummus::EStatusCode status = ExtractTablePlacements(inParser, inStartPage, inEndPage);
    if(status == eSuccess) {
        ComposeTables();
    }

    return status;
}

PDFHummus::EStatusCode TableExtraction::ExtractTables(IByteReaderWithPosition* inStream, long inStartPage, long inEndPage)  {
    EStatusCode status = eSuccess;

    ClearState();

    do {
        PDFParser parser;
        status = parser.StartPDFParsing(inStream);
        if(status != eSuccess)
        {
            LatestError.code = eErrorInternalPDFWriter;
            LatestError.description = string("Failed to parse file");
            break;
        }

        status = ExtractTablePlacements(&parser, inStartPage, inEndPage);
        if(status != eSuccess)
            break;

        ComposeTables();
    } while(false);

    return status;    
}



void TableExtraction::ComposeTables() {
    TableComposer tableComposer;
    ParsedTextPlacementListList::iterator itTextsforPages = textsForPages.begin();
    LinesList::iterator itTablesLinesForPages = tableLinesForPages.begin();
    PDFRectangleList::iterator itMediaBoxForPages = mediaBoxesForPages.begin();

    // iterate the pages (lists are supposed to be synced)
    for(; itTextsforPages != textsForPages.end() &&  
            itTablesLinesForPages != tableLinesForPages.end() && 
            itMediaBoxForPages != mediaBoxesForPages.end(); 
            ++itTextsforPages, ++itTablesLinesForPages, ++itMediaBoxForPages) {
        double pageScopeBox[4] ={itMediaBoxForPages->LowerLeftX, itMediaBoxForPages->LowerLeftY, itMediaBoxForPages->UpperRightX, itMediaBoxForPages->UpperRightY};
        tablesForPages.push_back(tableComposer.ComposeTables(*itTablesLinesForPages, *itTextsforPages, pageScopeBox));
    }
}

static const string scCRLN = "\r\n";

void TableExtraction::GetTableAsCSVText(const Table& inTable, int bidiFlag, TextComposer::ESpacing spacingFlag, std::ostream& outStream) {
    TableCSVExport exporter(bidiFlag, spacingFlag);
    exporter.ComposeTableText(inTable, outStream);
}

void TableExtraction::GetAllAsCSVText(int bidiFlag, TextComposer::ESpacing spacingFlag, std::ostream& outStream) {
    TableCSVExport exporter(bidiFlag, spacingFlag);

    TableListList::iterator itPages = tablesForPages.begin();

    for(; itPages != tablesForPages.end(); ++itPages) {
        TableList::iterator itTables = itPages->begin();
        for(; itTables != itPages->end(); ++itTables) {
            exporter.ComposeTableText(*itTables, outStream);
            outStream<<scCRLN; // two newlines to separate tables on the same page
            outStream<<scCRLN;
        }
        outStream<<scCRLN; // 4 newlines to separate pages
        outStream<<scCRLN;
        outStream<<scCRLN;
        outStream<<scCRLN;
    }
}
