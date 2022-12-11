#pragma once

#include <list>

#include "../math/Transformations.h"

#include "TextGraphicState.h"

struct ContentGraphicState {
    ContentGraphicState(): textGraphicState() {
        unitMatrix(ctm);
    }
    ContentGraphicState(const ContentGraphicState& otherState): textGraphicState(otherState.textGraphicState) {
        copyMatrix(otherState.ctm, ctm);
    }
    double ctm[6];
    TextGraphicState textGraphicState;
};