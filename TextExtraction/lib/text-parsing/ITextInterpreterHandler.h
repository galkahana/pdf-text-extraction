#pragma once

#include "ParsedTextPlacement.h"

class ITextInterpreterHandler {

public:
    virtual bool onParsedTextPlacementComplete(const ParsedTextPlacement& inParsedTextPlacement) = 0; 
};