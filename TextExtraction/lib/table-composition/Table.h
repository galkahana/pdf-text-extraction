#pragma once

#include "../table-line-parsing/ParsedLinePlacement.h"
#include "../text-parsing/ParsedTextPlacement.h"

#include <vector>
#include <list>

struct Table;

struct CellInRow {
    CellInRow(): leftLine(), rightLine(),textPlacements() {
        colSpan = 1;
        internalTable = NULL;
    }

    CellInRow(
        const ParsedLinePlacement& inLeftLine,
        const ParsedLinePlacement& inRightLine,
        int inColSpan,
        const ParsedTextPlacementList& inTextPlacements,
        Table* inInternalTable): leftLine(inLeftLine), rightLine(inRightLine), textPlacements(inTextPlacements) {
            colSpan = inColSpan;
            internalTable = inInternalTable;
    }

    CellInRow(const CellInRow& inOther); // this one DUPLICATES the table

    ~CellInRow();

    ParsedLinePlacement leftLine;
    ParsedLinePlacement rightLine;
    int colSpan;

    ParsedTextPlacementList textPlacements;
    
    Table* internalTable; // oh this is causing much trouble...but fear not...we'll just duplicate it as intended
};

typedef std::vector<CellInRow> CellInRowVector;

struct Row {
    ParsedLinePlacement topLine;
    ParsedLinePlacement bottomLine;

    CellInRowVector cells;
};

typedef std::vector<Row> RowVector;

struct Table {
    RowVector rows;
};

typedef std::list<Table> TableList;

