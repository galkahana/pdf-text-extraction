#pragma once

#include "../text-parsing/ParsedTextPlacement.h"

#include <string>
#include <list>
#include <sstream>
#include <ostream>

class TextComposer {
    public:

        enum ESpacing
        {
            eSpacingNone = 0,
            eSpacingHorizontal = 1,
            eSpacingVertical = 2,
            eSpacingBoth = 3
        };

        enum ENewLineStyle
        {
            eNewLineNative = 0,
            eNewLineLF = 1,
            eNewLineCRLF = 2
        };
    
        TextComposer(int inBidiFlag, ESpacing inSpacingFlag, ENewLineStyle inNewLineStyle);
        virtual ~TextComposer();

        const char* GetNewLine() const;


        void ComposeText(const ParsedTextPlacementList& inTextPlacements, std::ostream& outStream);

    private:
        int bidiFlag;
        ESpacing spacingFlag;
        ENewLineStyle newLineStyle;

    void MergeLineStreamToResultString(
        const std::stringstream& inStream, 
        int bidiFlag,
        bool shouldAddSpacesPerLines, 
        const double (&inLineBox)[4],
        const double (&inPrevLineBox)[4],
        std::ostream& outStream
    );


};