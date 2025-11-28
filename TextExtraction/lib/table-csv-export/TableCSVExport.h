# pragma once

#include "../text-composition/TextComposer.h"
#include "../table-composition/Table.h"
#include <ostream>

class TableCSVExport {
    public:
        TableCSVExport(int inBidiFlag, TextComposer::ESpacing inSpacingFlag);
        virtual ~TableCSVExport();


        void ComposeTableText(const Table& inTable, std::ostream& outStream);

    private:
        TextComposer textComposer;

        std::string GetCellText(const CellInRow& inCell);
        void Quote(const std::string& inString, std::ostream& outStream);

};