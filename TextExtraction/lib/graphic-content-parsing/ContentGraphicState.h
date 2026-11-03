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
        mcid = -1;
        artifact = false;
    }
    ContentGraphicState(const ContentGraphicState& otherState): textGraphicState(otherState.textGraphicState) {
        CopyMatrix(otherState.ctm, ctm);
        lineWidth = otherState.lineWidth;
        fillColorComponents = otherState.fillColorComponents;
        for(int i=0;i<4;++i)
            fillColor[i] = otherState.fillColor[i];
        mcid = otherState.mcid;
        artifact = otherState.artifact;
    }
    double ctm[6];
    double lineWidth;
    // nonstroking (fill) color, as set by g, rg, k, or by sc/scn in a Device color space.
    // fillColorComponents is the number of components of the fill color space: 1 DeviceGray,
    // 3 DeviceRGB, 4 DeviceCMYK, 0 any other (the color is then unknown, and fillColor is not meaningful)
    int fillColorComponents;
    double fillColor[4];
    // marked content the text or path is drawn in. not part of the graphic state proper (q/Q do not save or
    // restore marked content), so these are set only on the copies handed to the handler, in text placements
    // and painted paths. mcid is the innermost enclosing MCID (-1 for none), artifact is true when this or an
    // enclosing sequence is tagged /Artifact
    int mcid;
    bool artifact;
    TextGraphicState textGraphicState;
};