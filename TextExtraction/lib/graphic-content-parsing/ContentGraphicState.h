#pragma once

#include <list>

#include "../math/Transformations.h"

#include "TextGraphicState.h"

struct ContentGraphicState {
    ContentGraphicState(): textGraphicState() {
        UnitMatrix(ctm);
        lineWidth = 1;
    }
    ContentGraphicState(const ContentGraphicState& otherState): textGraphicState(otherState.textGraphicState) {
        CopyMatrix(otherState.ctm, ctm);
        lineWidth = otherState.lineWidth;
    }
    double ctm[6];
    double lineWidth;
    TextGraphicState textGraphicState;
};