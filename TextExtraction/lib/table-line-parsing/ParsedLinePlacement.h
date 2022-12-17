#pragma once

#include "../math/Transformations.h"
#include "../graphic-content-parsing/Path.h"

struct ParsedLinePlacement {
    ParsedLinePlacement(
        const double (&inLocalPointOne)[2],
        const double (&inLocalPointTwo)[2],
        const double (&inMatrix)[6],
        const double inLineWidth,
        bool inIsVertical,
        const double (&inGlobalPointOne)[2],
        const double (&inGlobalPointTwo)[2],
        const double (&inEffectiveLineWidth)[2]
    ) {
        CopyVector(inLocalPointOne, localPointOne);
        CopyVector(inLocalPointTwo, localPointTwo);
        CopyMatrix(inMatrix, matrix);
        lineWidth = inLineWidth;
        isVertical = inIsVertical;
        CopyVector(inGlobalPointOne, globalPointOne);
        CopyVector(inGlobalPointTwo, globalPointTwo);
        CopyVector(inEffectiveLineWidth, effectiveLineWidth);
    }

    double localPointOne[2];
    double localPointTwo[2];
	double matrix[6];
	double lineWidth;
    bool isVertical;

	// in vertical lines, globalPointOne is top, and globalPointTwo is bottom
	// in horizontal lines, globalPointOne is left, and globalPointTwo is right
    double globalPointOne[2];
    double globalPointTwo[2];
    // width having the matrix applied.
    double effectiveLineWidth[2];
};
