#pragma once

#include <list>

#include "Transformations.h"
#include "TextPlacement.h"

struct GraphicalState {
    GraphicalState(): text() {
        double arr[6] = {1,0,0,1,0,0};
        copyMatrix(arr, ctm);
    }
    GraphicalState(const GraphicalState& otherState): text(otherState.text) {
        copyMatrix(otherState.ctm, ctm);
    }
    double ctm[6];
    TextState text;
};

typedef std::list<TextState> TextStateList;
typedef std::list<GraphicalState> GraphicStateList;

class TPCollectionState {
public:
    TPCollectionState();
    virtual ~TPCollectionState();

    void PushGraphicState();
    void PopGraphicState();

    GraphicalState& CurrentGraphicState();
    TextState& CurrentTextState();
    void StartTextElement();
    void EndTextPlacement();

    void PushPlacedTextOperations(const PlacedTextCommandArgumentList& inOperations);

    TextElementList textElements;

private:
    bool isInTextElement;
    GraphicStateList graphicStateStack;
    TextStateList textElementTextStack;

    PlacedTextCommandList texts;
};
