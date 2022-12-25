#pragma once

#include "ParsedLinePlacement.h"

class ITableLineInterpreterHandler {

    public:
        virtual bool OnParsedHorizontalLinePlacementComplete(const ParsedLinePlacement& inParsedLine) = 0; 
        virtual bool OnParsedVerticalLinePlacementComplete(const ParsedLinePlacement& inParsedLine) = 0; 
};