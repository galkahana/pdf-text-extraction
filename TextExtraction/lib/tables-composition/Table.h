#pragma once

#include "../table-line-parsing/ParsedLinePlacement.h"
#include "../text-parsing/ParsedTextPlacement.h"

#include <vector>

struct CellInRow {
    ParsedLinePlacement leftLine;
    ParsedLinePlacement rightLine;
    int colSpan;

    ParsedTextPlacementList textPlacements;
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