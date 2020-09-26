#pragma once

#include <list>

#include "TextPlacement.h"

struct GraphicState {
    GraphicState(): text() {
        ctm[0] = ctm[3] = 1;
        ctm[1] = ctm[2] = ctm[4] = ctm[5] = 0;
    }
    GraphicState(const GraphicState& otherState): text(otherState.text) {
        for(int i=0;i<6;++i)
            ctm[i] = otherState.ctm[i];
    }
    double ctm[6];
    TextState text;
};

typedef std::list<TextState> TextStateList;
typedef std::list<GraphicState> GraphicStateList;

class TPCollectionState {
public:
    TPCollectionState();
    virtual ~TPCollectionState();

    void PushGraphicState();
    void PopGraphicState();

    GraphicState& CurrentGraphicState();
    TextState& CurrentTextState();
    void StartTextElement();
    void EndTextPlacement();

    void PushPlacedTextOperations(const PlacedTextRecordList& inOperations);

    PlacedTextOperationResultList texts;

private:
    bool isInTextElement;
    GraphicStateList graphicStateStack;
    TextStateList textElementTextStack;
};
