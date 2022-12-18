#pragma once

#include "Table.h"
#include "Lines.h"

#include "../text-parsing/ParsedTextPlacement.h"

class TableComposer {
    public:
        TableComposer();
        virtual ~TableComposer();

        TableList ComposeTables(const Lines& inLines, const ParsedTextPlacementList& inTextPlacements, const double (&inScopeBox)[4]);
};