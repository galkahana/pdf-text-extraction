#pragma once

#include "../pdf-writer-enhancers/Bytes.h"

#include "ContentGraphicState.h"
#include "TextGraphicState.h"

#include <string>
#include <list>
#include <vector>

// PlacedTextCommandArgument matches an argument to a text placement command.
// Mostly it'll be text, but for TJ it might be a text or a position
struct PlacedTextCommandArgument {
    PlacedTextCommandArgument(double inPos) {
        isText = false;
        pos = inPos;
    }

    PlacedTextCommandArgument(const ByteList& inBytes) {
        isText = true;
        bytes = inBytes;
    }

    // choice of what's represented
    bool isText;
    
    // text data
    ByteList bytes;

    // position data
    double pos;
};

typedef std::vector<PlacedTextCommandArgument> PlacedTextCommandArgumentVector;


// PlacedTextCommand matches a text placement command like TJ, Tj etc.
// the "text" param matches the list of arguments it got. most of the time it's a single
// text, but for TJ it might be an array of text of position
// graphicState and textState are snapshots of the current graphic and text states
struct PlacedTextCommand {
    PlacedTextCommandArgumentVector text;
    ContentGraphicState graphicState;
    TextGraphicState textState;
};

typedef std::list<PlacedTextCommand> PlacedTextCommandList;

// TextElement matches a pdf text element, which is what's between an BT...ET sequance.
struct TextElement {
    PlacedTextCommandList texts;
};