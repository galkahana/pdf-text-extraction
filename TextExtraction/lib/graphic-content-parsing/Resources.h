#pragma once

#include "RefCountPtr.h"
#include "PDFObject.h"

#include <map>

struct GSState {
    GSState(RefCountPtr<PDFObject> inRef, double inSize) {
        fontRef = inRef;
        fontSize = inSize;
    }

    RefCountPtr<PDFObject> fontRef;
    double fontSize;
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