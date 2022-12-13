#pragma once

#include "Path.h"
#include "ContentGraphicState.h"

enum EFillMethod {
    eFillMethodNonZeroWindingNumberRule,
    eFillMethodEventOddRule,
};

struct PathElement {
    Path path;
    ContentGraphicState graphicState;

    bool shouldStroke;
    bool shouldFill;
    EFillMethod fillMethod;
};