#pragma once

#include <list>

#include "../math/Transformations.h"

#include "TextGraphicState.h"

struct ContentGraphicState {
    ContentGraphicState(): textGraphicState() {
        UnitMatrix(ctm);
    }
    ContentGraphicState(const ContentGraphicState& otherState): textGraphicState(otherState.textGraphicState) {
        CopyMatrix(otherState.ctm, ctm);
    }
    double ctm[6];
    TextGraphicState textGraphicState;
};