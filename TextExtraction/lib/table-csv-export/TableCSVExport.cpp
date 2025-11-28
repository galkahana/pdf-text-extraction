#include "TableCSVExport.h"
#include <string>

using namespace std;

static const string scEmpty = "";
static const string scDoubleQuote = "\"";
static const char scDoubleQuoteChar = '\"';
static const string scComma = ",";
static const string scCRLN = "\r\n";

TableCSVExport::TableCSVExport(int inBidiFlag, TextComposer::ESpacing inSpacingFlag):textComposer(inBidiFlag, inSpacingFlag) {

}

TableCSVExport::~TableCSVExport() {

}

void TableCSVExport::Quote(const string& inString, std::ostream& outStream) {
    if(inString.length() == 0) {
        // don't quote if there's nothing and no need to introduce anything into the stream
        return;
    }

    outStream<<scDoubleQuote;
    string::const_iterator it = inString.begin();
    for(; it != inString.end();++it) {
        if(*it == scDoubleQuoteChar)
            outStream<<scDoubleQuote<<scDoubleQuote;
        else
            outStream<<*it;
    }
    outStream<<scDoubleQuote;
}

string TableCSVExport::GetCellText(const CellInRow& inCell) {
    std::stringstream cellStream;
    textComposer.ComposeText(inCell.textPlacements, cellStream);
    return cellStream.str();
}

void TableCSVExport::ComposeTableText(const Table& inTable, std::ostream& outStream) {
    RowVector::const_iterator itRows = inTable.rows.begin();

    for(; itRows != inTable.rows.end(); ++itRows) {
        CellInRowVector::const_iterator itCols = itRows->cells.begin();
        Quote(GetCellText(*itCols), outStream);
        ++itCols;
        for(; itCols != itRows->cells.end(); ++itCols) {
            outStream<<scComma;
            Quote(GetCellText(*itCols), outStream);
            for(int i = 1; i < itCols->colSpan;++i)
                outStream<<scComma;
        }
        outStream<<scCRLN;
    }
}




