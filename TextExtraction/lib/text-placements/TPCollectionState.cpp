#include "TPCollectionState.h"

TPCollectionState::TPCollectionState() {
    isInTextElement = false;
    graphicStateStack.push_back(GraphicalState());
}

TPCollectionState::~TPCollectionState() {
    graphicStateStack.clear();
    textElementTextStack.clear();
}

void TPCollectionState::PushGraphicState() {
    graphicStateStack.push_back(GraphicalState(graphicStateStack.back()));
    if(isInTextElement)
        textElementTextStack.push_back(TextState(textElementTextStack.back()));
}

void TPCollectionState::PopGraphicState() {
    if(graphicStateStack.size() > 1)
        graphicStateStack.pop_back();
    if(isInTextElement && textElementTextStack.size() > 1)
        textElementTextStack.pop_back();
}

GraphicalState& TPCollectionState::CurrentGraphicState() {
    return graphicStateStack.back();
}

TextState& TPCollectionState::CurrentTextState() {
    if(isInTextElement) {
        return textElementTextStack.back();
    }
    
    return graphicStateStack.back().text;
}

void TPCollectionState::StartTextElement() {
    isInTextElement = true;
    textElementTextStack.clear();
    textElementTextStack.push_back(TextState(graphicStateStack.back().text));
}

void TPCollectionState::EndTextPlacement() {
    isInTextElement = false;

    // copy persisted data to top text state
    TextState& source = textElementTextStack.back();
    TextState& target = graphicStateStack.back().text;
    target.charSpace = source.charSpace;
    target.wordSpace = source.wordSpace;
    target.scale = source.scale;
    target.leading = source.leading;
    target.rise = source.rise;
    target.fontRef = source.fontRef;
    target.fontSize = source.fontSize;

    textElementTextStack.clear();

    TextElement el = {PlacedTextCommandList(texts)};
    textElements.push_back(el);
    texts.clear();
}

void TPCollectionState::PushPlacedTextOperations(const PlacedTextCommandArgumentList& inOperations) {
    PlacedTextCommand el = {
        inOperations,
        {
            CurrentGraphicState().ctm[0],
            CurrentGraphicState().ctm[1],
            CurrentGraphicState().ctm[2],
            CurrentGraphicState().ctm[3],
            CurrentGraphicState().ctm[4],
            CurrentGraphicState().ctm[5]
        },
        TextState(CurrentTextState())
    };
    texts.push_back(el);
}