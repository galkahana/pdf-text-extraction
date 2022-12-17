#pragma once

#include "../text-parsing/ParsedTextPlacement.h"

#include <string>
#include <list>
#include <sstream>

typedef std::list<ParsedTextPlacement> ParsedTextPlacementList;

class TextComposer {
    public:

        enum ESpacing
        {
            eSpacingNone = 0,
            eSpacingHorizontal = 1,
            eSpacingVertical = 2,
            eSpacingBoth = 3
        };
    
        TextComposer(int inBidiFlag, ESpacing inSpacingFlag);
        virtual ~TextComposer();


        void ComposeText(const ParsedTextPlacementList& inTextPlacements);

        void AppendText(const std::string inText); // use this for extra chars

        std::string GetText();
        void Reset();

    private:
        int bidiFlag;
        ESpacing spacingFlag;
        std::stringstream buffer;

    void MergeLineStreamToResultString(
        const std::stringstream& inStream, 
        int bidiFlag,
        bool shouldAddSpacesPerLines, 
        const double (&inLineBox)[4],
        const double (&inPrevLineBox)[4]
    );


};