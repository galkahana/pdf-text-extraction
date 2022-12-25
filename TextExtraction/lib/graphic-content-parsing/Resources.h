#pragma once

#include "RefCountPtr.h"
#include "PDFObject.h"

#include <map>

struct GSState {
    GSState() {
        hasFont = false;
        hasLineWidth = false;
    }

    // Font
    bool hasFont;
    RefCountPtr<PDFObject> fontRef;
    double fontSize;

    // LineWidth
    bool hasLineWidth;
    double lineWidth;
};


typedef std::map<std::string, GSState> StringToGStateMap;


struct Font {
    Font(RefCountPtr<PDFObject> inRef) {
        fontRef = inRef;
    }

    RefCountPtr<PDFObject> fontRef;
};

typedef std::map<std::string, Font> StringToFontMap;

struct Resources {
    StringToGStateMap gStates;
    StringToFontMap fonts;
};