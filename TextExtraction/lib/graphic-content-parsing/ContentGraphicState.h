#pragma once

#include <list>

#include "../math/Transformations.h"

#include "TextGraphicState.h"

struct ContentGraphicState {
    ContentGraphicState(): textGraphicState() {
        UnitMatrix(ctm);
        lineWidth = 1;
        // initial fill color: DeviceGray black
        fillColorComponents = 1;
        fillColor[0] = fillColor[1] = fillColor[2] = fillColor[3] = 0;
    }
    ContentGraphicState(const ContentGraphicState& otherState): textGraphicState(otherState.textGraphicState) {
        CopyMatrix(otherState.ctm, ctm);
        lineWidth = otherState.lineWidth;
        fillColorComponents = otherState.fillColorComponents;
        for(int i=0;i<4;++i)
            fillColor[i] = otherState.fillColor[i];
    }
    double ctm[6];
    double lineWidth;
    // nonstroking (fill) color, as set by g, rg, k, or by sc/scn in a Device color space.
    // fillColorComponents is the number of components of the fill color space: 1 DeviceGray,
    // 3 DeviceRGB, 4 DeviceCMYK, 0 any other (the color is then unknown, and fillColor is not meaningful)
    int fillColorComponents;
    double fillColor[4];
    TextGraphicState textGraphicState;
};