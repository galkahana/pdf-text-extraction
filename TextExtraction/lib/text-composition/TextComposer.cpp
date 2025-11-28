#include "TextComposer.h"


#include "../bidi/BidiConversion.h"

#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

static const string scEmpty = "";
static const char scSpace = ' ';

void UnionLeftBoxToRight(const double (&inLeftBox)[4], double (&refRightBox)[4]) {
    // union left box to right box resulting in a box that contains both
    
    if(inLeftBox[0] < refRightBox[0])
        refRightBox[0] = inLeftBox[0];
    if(inLeftBox[1] < refRightBox[1])
        refRightBox[1] = inLeftBox[1];
    if(inLeftBox[2] > refRightBox[2])
        refRightBox[2] = inLeftBox[2];
    if(inLeftBox[3] > refRightBox[3])
        refRightBox[3] = inLeftBox[3];
}

double BoxHeight(const double (&inBox)[4]) {
    return inBox[3] - inBox[1];
}

double BoxWidth(const double (&inBox)[4]) {
    return inBox[2] - inBox[0];
}

double BoxTop(const double (&inBox)[4]) {
    return inBox[3];
}

double BoxBottom(const double (&inBox)[4]) {
    return inBox[1];
}


TextComposer::TextComposer(int inBidiFlag, ESpacing inSpacingFlag) {
    bidiFlag = inBidiFlag;
    spacingFlag = inSpacingFlag;
}

TextComposer::~TextComposer() {

}

const double LINE_HEIGHT_THRESHOLD = 5;

int GetOrientationCode(const ParsedTextPlacement& a) {
    // a very symplistic heuristics to try and logically group different text orientations in a way that makes sense

    // 1 0 0 1
    if(a.matrix[0] > 0 && a.matrix[3] > 0)
        return 0;

    // 0 1 -1 0
    if(a.matrix[1] > 0 && a.matrix[2] < 0)
        return 1;

    // -1 0 0 -1
    if(a.matrix[0] < 0 && a.matrix[3] < 0)
        return 2;

    // 0 -1 1 0 or other
    return 3;
}

bool CompareForOrientation(const ParsedTextPlacement& a, const ParsedTextPlacement& b, int code) {
    if(code == 0) {
        if(abs(a.globalBbox[1] - b.globalBbox[1]) > LINE_HEIGHT_THRESHOLD)
            return b.globalBbox[1] < a.globalBbox[1];
        else
            return a.globalBbox[0] < b.globalBbox[0];    

    } else if(code == 1) {
        if(abs(a.globalBbox[0] - b.globalBbox[0]) > LINE_HEIGHT_THRESHOLD)
            return a.globalBbox[0] <  b.globalBbox[0];
        else
            return a.globalBbox[1] < b.globalBbox[1];    

    } else if(code == 2) {
        if(abs(a.globalBbox[1] - b.globalBbox[1]) > LINE_HEIGHT_THRESHOLD)
            return a.globalBbox[1] < b.globalBbox[1];
        else
            return b.globalBbox[0] < a.globalBbox[0];    
           
    } else {
        // code 3
        if(abs(a.globalBbox[0] - b.globalBbox[0]) > LINE_HEIGHT_THRESHOLD)
            return b.globalBbox[0] < a.globalBbox[0];
        else
            return b.globalBbox[1] < a.globalBbox[1];    
    }
    
}

bool CompareParsedTextPlacement(const ParsedTextPlacement& a, const ParsedTextPlacement& b) {
    int codeA = GetOrientationCode(a);
    int codeB = GetOrientationCode(b);

    if(codeA == codeB) {
        return CompareForOrientation(a,b,codeA);
    }
    
    return codeA < codeB;
}

typedef std::vector<ParsedTextPlacement> ParsedTextPlacementVector;

bool AreSameLine(const ParsedTextPlacement& a, const ParsedTextPlacement& b) {
    int codeA = GetOrientationCode(a);
    int codeB = GetOrientationCode(b);

    if(codeA != codeB)
        return false;

    if(codeA == 0 || codeA == 2) {
        return abs(a.globalBbox[1] - b.globalBbox[1]) <= LINE_HEIGHT_THRESHOLD;
    } else {
        return abs(a.globalBbox[0] - b.globalBbox[0]) <= LINE_HEIGHT_THRESHOLD;
    }
}

unsigned long GuessHorizontalSpacingBetweenPlacements(const ParsedTextPlacement& left, const ParsedTextPlacement& right) {
    double leftTextRightEdge = left.globalBbox[2];
    double rightTextLeftEdge = right.globalBbox[0];

    if(leftTextRightEdge > rightTextLeftEdge)
        return 0; // left text is overflowing into right text

    double distance = rightTextLeftEdge - leftTextRightEdge;
    double spaceWidth = left.globalSpaceWidth[0];

    if(spaceWidth == 0 && BoxWidth(left.globalBbox) > 0) {
        // if no available space width from font info, try to evaluate per the left string width/char length...not the best...but
        // easy.
        spaceWidth = BoxWidth(left.globalBbox) / left.text.length();
    }

    if(spaceWidth == 0)
        return 0; // protect from 0 errors

    return (unsigned long)floor(distance/spaceWidth);
}

static const string scCRLN = "\r\n";

void TextComposer::MergeLineStreamToResultString(
    const stringstream& inStream, 
    int bidiFlag,
    bool shouldAddSpacesPerLines, 
    const double (&inLineBox)[4],
    const double (&inPrevLineBox)[4],
    std::ostream& outStream
) {
    BidiConversion bidi;

    // add spaces before line, per distance from last line
    if(shouldAddSpacesPerLines && BoxTop(inLineBox) < BoxBottom(inPrevLineBox)) {
        unsigned long verticalLines = floor((BoxBottom(inPrevLineBox) - BoxTop(inLineBox))/BoxHeight(inPrevLineBox));
        for(unsigned long i=0;i<verticalLines;++i)
            outStream<<scCRLN;
    }


    if(bidiFlag == -1) {
        outStream<<inStream.str();
    }
    else {
        string bidiResult;
        bidi.ConvertVisualToLogical(inStream.str(), bidiFlag, bidiResult); // returning status may be used to convey that's succeeded
        outStream<<bidiResult;
    }
}

void TextComposer::ComposeText(const ParsedTextPlacementList& inTextPlacements, std::ostream& outStream) {
    double lineBox[4];
    double prevLineBox[4];
    bool isFirstLine;
    bool addVerticalSpaces = spacingFlag & TextComposer::eSpacingVertical;
    bool addHorizontalSpaces = spacingFlag & TextComposer::eSpacingHorizontal;

    ParsedTextPlacementVector sortedTextCommands(inTextPlacements.begin(), inTextPlacements.end());
    sort(sortedTextCommands.begin(), sortedTextCommands.end(), CompareParsedTextPlacement);

    ParsedTextPlacementVector::iterator itCommands = sortedTextCommands.begin();
    if(itCommands == sortedTextCommands.end())
        return;

    // k. got some text, let's build it
    stringstream lineResult;
    ParsedTextPlacement& latestItem = *itCommands;
    bool hasPreviousLineInPage = false;
    CopyBox(itCommands->globalBbox, lineBox);
    lineResult<<latestItem.text;
    ++itCommands;
    for(; itCommands != sortedTextCommands.end();++itCommands) {
        if(AreSameLine(latestItem, *itCommands)) {
            if(addHorizontalSpaces) {
                unsigned long spaces = GuessHorizontalSpacingBetweenPlacements(latestItem, *itCommands);
                if(spaces != 0)
                    lineResult<<string(spaces, scSpace);
            }
            UnionLeftBoxToRight(itCommands->globalBbox, lineBox);
        } else {
            // merge complete line to accumulated text, and start a fresh line with fresh accumulators
            MergeLineStreamToResultString(lineResult, bidiFlag ,addVerticalSpaces && hasPreviousLineInPage, lineBox, prevLineBox, outStream);
            outStream<<scCRLN;
            lineResult.str(scEmpty);
            CopyBox(lineBox, prevLineBox);
            CopyBox(itCommands->globalBbox, lineBox);
            hasPreviousLineInPage = true;
        }
        lineResult<<itCommands->text;
        latestItem = *itCommands;
    }
    MergeLineStreamToResultString(lineResult, bidiFlag ,addVerticalSpaces && hasPreviousLineInPage, lineBox, prevLineBox, outStream);

}

