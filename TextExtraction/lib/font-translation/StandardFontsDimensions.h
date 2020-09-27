#pragma once

#include <map>
#include <string>


typedef std::map<unsigned long,double> ULongToDoubleMap;

struct FontWidthDescriptor {
    FontWidthDescriptor():widths() {
        ascent = 0;
        descent = 0;
        isMonospaced = 0;
        monospaceWidth = 0;
    }

    FontWidthDescriptor(double inAscent,double  inDescent,double inMonospaceWidth) {
            ascent = inAscent;
            descent = inDescent; // haha
            monospaceWidth = inMonospaceWidth;
            isMonospaced = true;
    }

    FontWidthDescriptor(double inAscent,double  inDescent, const ULongToDoubleMap& inWidths) {
            ascent = inAscent;
            descent = inDescent;
            isMonospaced = false;
            monospaceWidth = 0; // because reasons
            widths = inWidths;
    }

    double ascent;
    double descent;
    bool isMonospaced;
    double monospaceWidth;
    ULongToDoubleMap widths;
};

typedef std::map<std::string,FontWidthDescriptor> StringToFontWidthDescriptorMap;

class StandardFontsDimensions {
    public:
        StandardFontsDimensions();

        const FontWidthDescriptor* FindStandardFont(const std::string& inFontName) const;
        
    private:
        StringToFontWidthDescriptorMap fonts;
};