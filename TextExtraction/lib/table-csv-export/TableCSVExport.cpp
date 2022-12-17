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

void TableCSVExport::Quote(const string& inString) {
    if(inString.length() == 0) {
        // don't quote if there's nothing and no need to introduce anything into the buffer
        return;
    }

    buffer<<scDoubleQuote;
    string::const_iterator it = inString.begin();
    for(; it != inString.end();++it) {
        if(*it == scDoubleQuoteChar)
            buffer<<scDoubleQuote<<scDoubleQuote;
        else
            buffer<<*it;
    }
    buffer<<scDoubleQuote;
}

string TableCSVExport::GetCellText(const CellInRow& inCell) {
    textComposer.ComposeText(inCell.textPlacements);
    string cellText = textComposer.GetText();
    textComposer.Reset();

    return cellText;
}

void TableCSVExport::ComposeTableText(const Table& inTable) {
    RowVector::const_iterator itRows = inTable.rows.begin();

    for(; itRows != inTable.rows.end(); ++itRows) {
        CellInRowVector::const_iterator itCols = itRows->cells.begin();
        Quote(GetCellText(*itCols));
        ++itCols;
        for(; itCols != itRows->cells.end(); ++itCols) {
            buffer<<scComma;
            Quote(GetCellText(*itCols));
            for(int i = 1; i < itCols->colSpan;++i)
                buffer<<scComma;
        }
        buffer<<scCRLN;
    }
}

void TableCSVExport::AppendText(const std::string inText) {
    buffer<<inText;
}

std::string TableCSVExport::GetText() {
    return buffer.str();
}

void TableCSVExport::Reset() {
    buffer.str(scEmpty);
}


