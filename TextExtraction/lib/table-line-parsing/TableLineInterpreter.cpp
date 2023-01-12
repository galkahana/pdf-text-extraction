#include "TableLineInterpreter.h"

#include <math.h>
#include <set>

using namespace std;

// Threshould for rounding issues with transforming double numbers
#define DOUBLE_EPSILON 0.005
// Threshold for filtering non line rectangles, max width for what is considered a line and not a rectangle.
// One inch would do
#define MAX_LINE_WIDTH 72


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

bool IsEpsilonEqual(double A, double B) {
    return abs(A - B) < DOUBLE_EPSILON;
}

void TransformPathPoint(const PathPoint& inPathPoint, const double (&inMatrix)[6] , double (&outTransformedPoint)[2]) {
    double localPoint[2] = {inPathPoint.x, inPathPoint.y};

    TransformVector(localPoint, inMatrix, outTransformedPoint);
}

bool TableLineInterpreter::OnStrokePathPainted(const PathElement& inPathElement) {
    bool shouldContinue = true;

    SubPathList::const_iterator it = inPathElement.path.subPaths.begin();
    for(; it != inPathElement.path.subPaths.end() && shouldContinue; ++it) {
        // acceptable subpaths are 2 points paths that are either vertical or horizontal

        if(it->components.size() != 2)
            continue;
        
        // 2 components...just make sure they are not curves
        bool hasCurve = false;

        PathComponentList::const_iterator itPoints = it->components.begin();
        for(;itPoints != it->components.end() && !hasCurve;++itPoints) {
            hasCurve = itPoints->isCubicBezier;
        }

        if(hasCurve) {
            continue;
        }

        // for this line to be horizontal or vertical, xs needs to be the same or ys need to be the same (allowing for double mischief in the form of EPSILON)
        // note that for extra safety this property of them must be relevant to those points AFTER having applied the transformation matrix applied to this path graphic state
        double globalPointOne[2];
        double globalPointTwo[2];
        itPoints = it->components.begin();

        TransformPathPoint(itPoints->to, inPathElement.graphicState.ctm, globalPointOne);
        TransformPathPoint((++itPoints)->to, inPathElement.graphicState.ctm, globalPointTwo);
        
        // compute effective width
        double widthVector[2] = {inPathElement.graphicState.lineWidth, inPathElement.graphicState.lineWidth};
        double globalWidthVector[2];
        double scaleMatrix[6];
        CopyMatrix(inPathElement.graphicState.ctm, scaleMatrix);
        scaleMatrix[4] = scaleMatrix[5] = 0;
        TransformVector(widthVector, scaleMatrix, globalWidthVector);
        globalWidthVector[0] = abs(globalWidthVector[0]);
        globalWidthVector[1] = abs(globalWidthVector[1]);

        if(globalWidthVector[0] > MAX_LINE_WIDTH || globalWidthVector[1] > MAX_LINE_WIDTH)
            continue; // this is a rectangle, not a line

        if(IsEpsilonEqual(globalPointOne[0], globalPointTwo[0])) {
            // x is the same, so vertical line

            bool isOneTheTop = globalPointOne[1] > globalPointTwo[1];

            ParsedLinePlacement linePlacement(
                true,
                isOneTheTop ? globalPointOne : globalPointTwo,
                isOneTheTop ? globalPointTwo : globalPointOne,
                globalWidthVector
            );

            shouldContinue =  handler->OnParsedVerticalLinePlacementComplete(linePlacement);
        } else if(IsEpsilonEqual(globalPointOne[1], globalPointTwo[1])) {
            // y is the same, so horizontal line

            bool isOneTheLeft = globalPointOne[0] < globalPointTwo[0];

            ParsedLinePlacement linePlacement(
                false,
                isOneTheLeft ? globalPointOne : globalPointTwo,
                isOneTheLeft ? globalPointTwo : globalPointOne,
                globalWidthVector

            );

            shouldContinue = handler->OnParsedHorizontalLinePlacementComplete(linePlacement);
        }
    
    }

    return shouldContinue;
}

bool IsEpsilonSmallerOrEqual(double A, double B) {
    return IsEpsilonEqual(A,B) || A < B;
}

typedef set<double (*)[2]> PointSet;

bool TableLineInterpreter::OnFillPathPainted(const PathElement& inPathElement) {
    // so turnes out lines can be drawn as filled rectangles...this method takes care of recording those
    // i'm gonna be looking at 5 points subpaths that represent rectangles (4 rectangle points and 5th which should be equal to the first). 
    // for a rectangle it should be that there's an a1,b1 and a2,b1 where the other points are a1,b2 and a2,b1

    bool shouldContinue = true;

    SubPathList::const_iterator it = inPathElement.path.subPaths.begin();
    for(; it != inPathElement.path.subPaths.end() && shouldContinue; ++it) {
        if(it->components.size() != 5)
            continue;
        
        // 5 components...just make sure they are not curves
        bool hasCurve = false;

        PathComponentList::const_iterator itPoints = it->components.begin();
        for(;itPoints != it->components.end() && !hasCurve;++itPoints) {
            hasCurve = itPoints->isCubicBezier;
        }

        if(hasCurve) {
            continue;
        }

        // and make sure the last one is the same as the first one
        if(it->components.back().to.x != it->components.front().to.x ||
            it->components.back().to.y != it->components.front().to.y
        )
            continue;

        // first, lets figure out if this is a valid rectangle. gonna check this on global so as not to risk the matrix changing this artifact
        double globalPointOne[2];
        double globalPointTwo[2];
        double globalPointThree[2];
        double globalPointFour[2];
        PointSet rectPoints;
        itPoints = it->components.begin();

        TransformPathPoint(itPoints->to, inPathElement.graphicState.ctm,globalPointOne);
        TransformPathPoint((++itPoints)->to, inPathElement.graphicState.ctm,globalPointTwo);
        TransformPathPoint((++itPoints)->to, inPathElement.graphicState.ctm,globalPointThree);
        TransformPathPoint((++itPoints)->to, inPathElement.graphicState.ctm,globalPointFour);

        rectPoints.insert(&globalPointOne);
        rectPoints.insert(&globalPointTwo);
        rectPoints.insert(&globalPointThree);
        rectPoints.insert(&globalPointFour);

        // now lets figure out roles. find the lower left point of the 4
        PointSet::iterator itRectPoints = rectPoints.begin();
        double (*lowerLeft)[2] = *itRectPoints;
        double (*upperRight)[2] = *itRectPoints;
        ++itPoints;
        for(; itRectPoints != rectPoints.end(); ++ itRectPoints) {
            double (*currentPoint)[2] = *itRectPoints;
            if(IsEpsilonSmallerOrEqual((*currentPoint)[0], (*lowerLeft)[0]) && IsEpsilonSmallerOrEqual((*currentPoint)[1], (*lowerLeft)[1]))
                lowerLeft = currentPoint;

            if(IsEpsilonSmallerOrEqual((*upperRight)[0], (*currentPoint)[0]) && IsEpsilonSmallerOrEqual((*upperRight)[1], (*currentPoint)[1]))
                upperRight = currentPoint;
        }

        rectPoints.erase(lowerLeft);
        rectPoints.erase(upperRight);

        // the remaining 2 points in the set should be the upper left and lower right
        double (*upperLeft)[2] = NULL;
        double (*lowerRight)[2] = NULL;

        itRectPoints = rectPoints.begin();
        for(; itRectPoints != rectPoints.end(); ++ itRectPoints) {
            double (*currentPoint)[2] = *itRectPoints;
            if(IsEpsilonEqual((*currentPoint)[0], (*lowerLeft)[0]) && IsEpsilonEqual((*currentPoint)[1], (*upperRight)[1]))
                upperLeft = currentPoint;

            if(IsEpsilonEqual((*currentPoint)[1], (*lowerLeft)[1]) && IsEpsilonEqual((*currentPoint)[0], (*upperRight)[0]))
                lowerRight = currentPoint;

        }

        // this is a valid rectangle if none of upperLeft or lowerRight is null and both are different
        if(!upperLeft || !lowerRight || upperLeft == lowerRight)
            continue;

    
        // now we can describe this as a line...question...is it vertical or horizontal...the judge would be 
        // which is larger - width or height. and the line would be the middle of the rect with line width being
        // the rect width/height (depending if vertical or horizontal). linewidth is ignored given that fill 
        // ignores linewidth

        double width = (*upperRight)[0] - (*lowerLeft)[0];
        double height = (*upperRight)[1] - (*lowerLeft)[1];

        
        if(width < height) {

            if(width > MAX_LINE_WIDTH)
                continue; // this is a rectangle, not a line

            // width smaller than height, so we'll consider this a vertical line
            double x = (*lowerLeft)[0] + width/2;

            double top[2] = {x, (*upperRight)[1]};
            double bottom[2] = {x, (*lowerLeft)[1]};
            double widthVector[2] = {width, width};

            ParsedLinePlacement linePlacement(
                true,
                top,
                bottom,
                widthVector
            );

            shouldContinue = handler->OnParsedVerticalLinePlacementComplete(linePlacement);
        } else {

            if(height > MAX_LINE_WIDTH)
                continue; // this is a rectangle, not a line
            
            // width is higher (or the same in which case we'll default to as if higher), so we'll consider this a horizontal line
            double y = (*lowerLeft)[1] + height/2;

            double left[2] = {(*lowerLeft)[0], y};
            double right[2] = {(*upperRight)[0], y};
            double widthVector[2] = {height, height};

            ParsedLinePlacement linePlacement(
                false,
                left,
                right,
                widthVector
            );

            shouldContinue = handler->OnParsedHorizontalLinePlacementComplete(linePlacement);
        }
    
    }

    return shouldContinue;    
}

bool TableLineInterpreter::OnPathPainted(const PathElement& inPathElement) {
    // i'm looking for subpaths where the whole subpath is a vertical or horizontal line.
    return !handler || ((!inPathElement.shouldStroke || OnStrokePathPainted(inPathElement)) && (!inPathElement.shouldFill || OnFillPathPainted(inPathElement)));
}