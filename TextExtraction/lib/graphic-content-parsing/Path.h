#pragma once

#include <list>

struct PathPoint {
    PathPoint() {
        x=0;
        y=0;
    }

    PathPoint(double inX, double inY) {
        x=inX;
        y=inY;
    }


    PathPoint(const PathPoint& inOtherPoint) {
        x = inOtherPoint.x;
        y = inOtherPoint.y;
    }
    
    double x;
    double y;
};


struct PathComponent {
    PathComponent():to(),control1(),control2() {
        isCubicBezier = false;
    }

    PathComponent(const PathPoint& inTo):to(inTo),control1(),control2() { // for straight lines
        isCubicBezier = false;
    }

    PathComponent(const PathPoint& inTo, const PathPoint inControl1, const PathPoint inControl2):to(inTo),control1(inControl1),control2(inControl2) { // for bezier curve
        isCubicBezier = true;
    }

    PathComponent(const PathComponent& inOther):to(inOther.to),control1(inOther.control1),control2(inOther.control2) {
        isCubicBezier = inOther.isCubicBezier;
    }

    PathPoint to;
    bool isCubicBezier;
    PathPoint control1;
    PathPoint control2;
};


typedef std::vector<PathComponent> PathComponentList;

struct SubPath {
    SubPath():components() {
        isClosed = false;
    }

    SubPath(const SubPath& inOther):components(inOther.components) {
        isClosed = inOther.isClosed;
    }


    PathComponentList components;
    bool isClosed;
};


typedef std::vector<SubPath> SubPathList;

/**
 *  A bit about how paths and subpaths and current point n such are expected to work in this representation.
 *  
 * Each subpath first point is where its starts. later points are meant to be either lineto or curveto from the previous
 * path component "to" point.
 * 
 * "m" and "re" commands explictly start a new subpath. 
 * "h" and "re" commands explictly close the current subpath. closing explicitly adds the first point as the last point and sets isClosed = true.
 *
 * any commands that add path components relative to the current point - "l", "c", "v" or "y" - add those components to 
 * the current subpath as long as its not closed. If it is closed, the last line of the last subpath (aka the current point) is used
 * as the first point of a new subpath and the new path components are added to this new subpath.
 * 
 * Implementing path/subpath relationship this way makes each subpath easy to understand independently with no ambiguity as to what
 * the first point might mean.
 */

struct Path {
    Path():subPaths() {
    }

    Path(const Path& inOther):subPaths(inOther.subPaths) {
    }

    SubPathList subPaths;
};