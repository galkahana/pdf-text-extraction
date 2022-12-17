#include "TableLineInterpreter.h"

#include <math.h>

#define DOUBLE_EPSILON 0.5

TableLineInterpreter::TableLineInterpreter(void) {
    SetHandler(NULL);
}
        
TableLineInterpreter::TableLineInterpreter(ITableLineInterpreterHandler* inHandler) {
    SetHandler(inHandler);
}

TableLineInterpreter::~TableLineInterpreter(void) {

}


void TableLineInterpreter::SetHandler(ITableLineInterpreterHandler* inHandler) {
    handler = inHandler;
}

bool TableLineInterpreter::OnPathPainted(const PathElement& inPathElement) {
    // i'm looking for paths where the whole path is a vertical or horizontal line.
    // now...it might be that someone has multiple lines in the same path...though not common....currently left out.

    if(!handler)
        return true;

    // has to be stroke otherwise not line
    if(!inPathElement.shouldStroke)
        return true;

    // for this to be a line we need all subpaths but one to be with 1 or 0 points (meaning at most someone did moveto)
    // and have one path of 2 lines which are not curves
    const SubPath* lineSubPath = NULL;
    SubPathList::const_iterator it = inPathElement.path.subPaths.begin();
    for(; it != inPathElement.path.subPaths.end(); ++it) {
        if(it->components.size() < 2)
            continue;
        
        if(it->components.size() > 2) {
            lineSubPath = NULL;
            break;
        }

        // 2 components...but there's already a lineSubPath...so means there's at least 2 lines/curves...not a line path
        if(lineSubPath) {
            lineSubPath = NULL;
            break;
        }

        // 2 components...just make sure they are not curves
        bool hasCurve = false;

        PathComponentList::const_iterator itPoints = it->components.begin();
        for(;itPoints != it->components.end() && !hasCurve;++itPoints) {
            hasCurve = itPoints->isCubicBezier;
        }

        if(hasCurve) {
            lineSubPath = NULL;
            break;
        }

        lineSubPath = &(*it);
    }

    if(!lineSubPath)
        return true;


    // for this line to be horizontal or vertical, xs needs to be the same or ys need to be the same (allowing for double mischief in the form of EPSILON)
    // note that for extra safety this property of them must be relevant to those points AFTER having applied the transformation matrix applied to this path graphic state
    PathPoint localPathPointOne(lineSubPath->components.begin()->to);
	PathPoint localPathPointTwo((++lineSubPath->components.begin())->to);
    
    double localPointOne[2] = {localPathPointOne.x, localPathPointOne.y};
    double localPointTwo[2] = {localPathPointTwo.x, localPathPointTwo.y};

    double globalPointOne[2];
    double globalPointTwo[2];

    TransformVector(localPointOne, inPathElement.graphicState.ctm,globalPointOne);
    TransformVector(localPointTwo, inPathElement.graphicState.ctm,globalPointTwo);

    // compute effective width. see the effect of scale
    double widthVector[2] = {inPathElement.graphicState.lineWidth, inPathElement.graphicState.lineWidth};
    double globalWidthVector[2];
    double scaleMatrix[6];
    CopyMatrix(inPathElement.graphicState.ctm, scaleMatrix);
    scaleMatrix[4] = scaleMatrix[5] = 0;
    TransformVector(widthVector, scaleMatrix, globalWidthVector);
    globalWidthVector[0] = abs(globalWidthVector[0]);
    globalWidthVector[1] = abs(globalWidthVector[1]);

    if(abs(globalPointOne[0] - globalPointTwo[0]) < DOUBLE_EPSILON) {
        // x is the same, so vertical line

        bool isOneTheTop = globalPointOne[1] > globalPointTwo[1];

        ParsedLinePlacement linePlacement(
            localPointOne,
            localPointTwo,
            inPathElement.graphicState.ctm,
            inPathElement.graphicState.lineWidth,
            true,
            isOneTheTop ? globalPointOne : globalPointTwo,
            isOneTheTop ? globalPointTwo : globalPointOne,
            globalWidthVector
        );

        return handler->OnParsedVerticalLinePlacementComplete(linePlacement);
    } else if(abs(globalPointOne[1] - globalPointTwo[1]) < DOUBLE_EPSILON) {
        // y is the same, so horizontal line

        bool isOneTheLeft = globalPointOne[0] < globalPointTwo[0];

        ParsedLinePlacement linePlacement(
            localPointOne,
            localPointTwo,
            inPathElement.graphicState.ctm,
            inPathElement.graphicState.lineWidth,
            false,
            isOneTheLeft ? globalPointOne : globalPointTwo,
            isOneTheLeft ? globalPointTwo : globalPointOne,
            globalWidthVector

        );

        return handler->OnParsedHorizontalLinePlacementComplete(linePlacement);
    }

    return true;
}