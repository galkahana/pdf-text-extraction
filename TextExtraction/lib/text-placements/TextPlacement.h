#pragma once

#include "RefCountPtr.h"
#include "PDFObject.h"
#include "Bytes.h"

#include <string>
#include <list>


enum ETranslationMethod {
    eTranslationMethodToUnicode,
    eTranslationMethodSimpleEncoding,
    eTranslationMethodDefault
};

struct PlacedTextRecord {
    PlacedTextRecord(double inPos) {
        isText = false;
        pos = inPos;
    }

    PlacedTextRecord(const std::string& inEncodedText, const ByteList& inBytes) {
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

typedef std::list<PlacedTextRecord> PlacedTextRecordList;

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

struct PlacedTextOperationResult {
    // Provided by first phase, of extraction
    PlacedTextRecordList text;
    double ctm[6];
    TextState textState;

    // Provided by second phase, of translation
    ETranslationMethod allTextTranslationMethod;
    std::string allTextAsText;
    ByteList allTextAsBytes;
};

typedef std::list<PlacedTextOperationResult> PlacedTextOperationResultList;


// This is for end result...might not be fitting here....
struct TextPlacement {
    std::string text;
    double matrix[6];
    double localBbox[4];
    double globalBbox[4];
};


// can be used to represent all text placements, or all text placements in a page
typedef std::list<TextPlacement> TextPlacementList;