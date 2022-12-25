#include "Table.h"


// now completing the CellInRow stuff when table is now known
CellInRow::CellInRow(const CellInRow& inOther):leftLine(inOther.leftLine), rightLine(inOther.rightLine), textPlacements(inOther.textPlacements){
        colSpan = inOther.colSpan;
        internalTable = inOther.internalTable == NULL ? NULL : new Table(*inOther.internalTable);
}

CellInRow::~CellInRow() {
    delete internalTable; // IMPORTANT, cause pointer!
}