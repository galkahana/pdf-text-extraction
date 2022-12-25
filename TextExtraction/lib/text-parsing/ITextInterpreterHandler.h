#pragma once

#include "ParsedTextPlacement.h"

class ITextInterpreterHandler {

public:
    virtual bool OnParsedTextPlacementComplete(const ParsedTextPlacement& inParsedTextPlacement) = 0; 
};