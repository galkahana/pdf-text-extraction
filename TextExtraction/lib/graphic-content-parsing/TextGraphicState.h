#pragma once

#include "RefCountPtr.h"
#include "PDFObject.h"
#include "../math/Transformations.h"

struct TextGraphicState {
    TextGraphicState():fontRef() {
        charSpace = 0;
        wordSpace = 0;
        scale = 100;
        leading = 0;
        rise = 0;
        unitMatrix(tm);
        unitMatrix(tlm);
        tmDirty = true;
        tlmDirty = true;
        fontSize = 0;
    }

    TextGraphicState(const TextGraphicState& inOther) {
        charSpace = inOther.charSpace;
        wordSpace = inOther.wordSpace;
        scale = inOther.scale;
        leading = inOther.leading;
        rise = inOther.rise;
        copyMatrix(inOther.tm, tm);
        copyMatrix(inOther.tlm, tlm);
        tmDirty = inOther.tmDirty;
        tlmDirty = inOther.tlmDirty;
        fontRef = inOther.fontRef;
        fontSize = inOther.fontSize;
    }

    double charSpace;
    double wordSpace;
    double scale;
    double leading;
    double rise;
    // font
    double tm[6];
    double tlm[6];
    bool tmDirty;
    bool tlmDirty;
    RefCountPtr<PDFObject> fontRef;
    double fontSize;
};