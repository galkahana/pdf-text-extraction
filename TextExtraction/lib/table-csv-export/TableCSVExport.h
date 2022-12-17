# pragma once

#include "../text-composition/TextComposer.h"
#include "../tables-composition/Table.h"

class TableCSVExport {
    public:
        TableCSVExport(int inBidiFlag, TextComposer::ESpacing inSpacingFlag);
        virtual ~TableCSVExport();


        void ComposeTableText(const Table& inTable);

        void AppendText(const std::string inText); // use this for extra chars

        std::string GetText();
        void Reset();

    private:
        TextComposer textComposer;
        std::stringstream buffer;

        std::string GetCellText(const CellInRow& inCell);
        void Quote(const std::string& inString);

};