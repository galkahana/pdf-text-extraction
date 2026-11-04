#pragma once

#include "ObjectsBasicTypes.h"
#include "ContentGraphicState.h"

class PDFStreamInput;

// an image XObject painted with Do. it covers the unit square under graphicState.ctm, and graphicState
// also carries the marked content it is drawn in (mcid, artifact). image is the image stream, valid
// during the call only, and not read
struct ImageElement {
    ObjectIDType objectID;
    PDFStreamInput* image;
    ContentGraphicState graphicState;
};
