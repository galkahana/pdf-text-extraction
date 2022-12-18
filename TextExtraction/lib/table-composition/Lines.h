#pragma once

#include "../table-line-parsing/ParsedLinePlacement.h"

#include <list>

typedef std::list<ParsedLinePlacement> ParsedLinePlacementList;

// collection of vertical and horizontal lines. can represent lines on a page or lines of a table
struct Lines {
    ParsedLinePlacementList verticalLines;
    ParsedLinePlacementList horizontalLines;
};

typedef std::list<Lines> LinesList;
