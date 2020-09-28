#pragma once

#include "RefCountPtr.h"
#include "PDFObject.h"

#include "../pdf-writer-enhancers/Bytes.h"
#include "../font-translation/Translation.h"

#include "Transformations.h"

#include <string>
#include <list>



// PlacedTextCommandArgument matches an argument to a text placement command.
// Mostly it'll be text, but for TJ it might be a text or a position
struct PlacedTextCommandArgument {
    PlacedTextCommandArgument(double inPos) {
        isText = false;
        pos = inPos;
    }

    PlacedTextCommandArgument(const std::string& inEncodedText, const ByteList& inBytes) {
        isText = true;
        asEncodedText = inEncodedText;
        asBytes = inBytes;
    }

    // Provided by first phase, of extraction

    // choice of what's represented
    bool isText;
    
    // as text
    std::string asEncodedText;
    ByteList asBytes;

    // as position
    double pos;

    // Provided by 2nd phase, of translation
    ETranslationMethod translationMethod;
    std::string asText;

};

typedef std::list<PlacedTextCommandArgument> PlacedTextCommandArgumentList;

struct TextState {
    TextState():fontRef() {
        charSpace = 0;
        wordSpace = 0;
        scale = 100;
        leading = 0;
        rise = 0;
        tm[0] = tm[3] = 1;
        tm[1] = tm[2] = tm[4] = tm[5] = 0;
        tlm[0] = tlm[3] = 1;
        tlm[1] = tlm[2] = tlm[4] = tlm[5] = 0;
        tmDirty = true;
        tlmDirty = true;
        fontSize = 0;
    }

    TextState(const TextState& inOther) {
        charSpace = inOther.charSpace;
        wordSpace = inOther.wordSpace;
        scale = inOther.scale;
        leading = inOther.leading;
        rise = inOther.rise;
        for(int i=0;i<6;++i)
            tm[i] = inOther.tm[i];
        for(int i=0;i<6;++i)
            tlm[i] = inOther.tlm[i];
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

// PlacedTextCommand matches a text placement command like TJ, Tj etc.
// the "text" param matches the list of arguments it got. most of the time it's a single
// text, but for TJ it might be an array of text of position
struct PlacedTextCommand {
    // Provided by first phase, of extraction
    PlacedTextCommandArgumentList text;
    double ctm[6];
    TextState textState; // tm member updated by third phase, of dimensions computation

    // Provided by second phase, of translation
    ETranslationMethod allTextTranslationMethod;
    std::string allTextAsText;
    ByteList allTextAsBytes;

    // Provided by third phase, of dimensions computation
    double localBBox[4];
};

typedef std::list<PlacedTextCommand> PlacedTextCommandList;

// TextElement matches a pdf text element, which is what's between an BT...ET sequance.
// Text element boundaries provide some hints for later attempts to determine the end result text
// and what goes with what
struct TextElement {
    PlacedTextCommandList texts;
};

typedef std::list<TextElement> TextElementList;


struct ResultTextCommand {
    ResultTextCommand(
        const std::string& inText,
        const double (&inMatrix)[6],
        const double (&inLocalBox)[4],
        const double (&inGlobalBox)[4]
    ) {
        text = inText;
        copyMatrix(inMatrix, matrix);
        copyBox(inLocalBox, localBbox);
        copyBox(inGlobalBox, globalBbox);
    }

    std::string text;
    double matrix[6];
    double localBbox[4];
    double globalBbox[4];
};


// can be used to represent all text placements, or all text placements in a page
typedef std::list<ResultTextCommand> ResultTextCommandList;