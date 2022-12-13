#pragma once

#include "../math/Transformations.h"
#include "../graphic-content-parsing/Path.h"

struct ParsedLinePlacement {
    ParsedLinePlacement(
        const double (&inLocalPointOne)[2],
        const double (&inLocalPointTwo)[2],
        const double (&inMatrix)[6],
        const double inLineWidthWidth,
        const double (&inGlobalPointOne)[2],
        const double (&inGlobalPointTwo)[2]
    ) {
        CopyVector(inLocalPointOne, localPointOne);
        CopyVector(inLocalPointTwo, localPointTwo);
        CopyMatrix(inMatrix, matrix);
        lineWidth = inLineWidthWidth;
        CopyVector(inGlobalPointOne, globalPointOne);
        CopyVector(inGlobalPointTwo, globalPointTwo);
    }

    double localPointOne[2];
    double localPointTwo[2];
	double matrix[6];
	double lineWidth;

	// in vertical lines, globalPointOne is top, and globalPointTwo is bottom
	// in horizontal lines, globalPointOne is left, and globalPointTwo is right
    double globalPointOne[2];
    double globalPointTwo[2];
};
