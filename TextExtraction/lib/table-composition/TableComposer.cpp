#include "TableComposer.h"

#include "../graphs/Graph.h"
#include "../graphs/Result.h"

#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include <math.h>
#include <iterator>

using namespace std;

TableComposer::TableComposer() {
/**
 * defining SHOULD_PARSE_INTERNAL_TABLES as flag while retaining shouldParseInternalTables
 * as boolean might not be the most efficient ways of implementing this, but it does allow me
 * to compile the parsing part...which i couldn't if i ifdefed the whole recursion section at CreateTable.
 * 
 * so - compile flag determines this boolean consulted in code.
 * 
 * why not do it (which is the default)? cause CSV output cant really use it and that's the only current output. so we can save some time.
 * why do it? cause it gives enough information to all defining split cells if outputting to some more sophisticated spreadsheet (like Excel, Google sheet, numbers)
 */

#ifdef SHOULD_PARSE_INTERNAL_TABLES
    shouldParseInternalTables = true;
#else // SHOULD_PARSE_INTERNAL_TABLES
    shouldParseInternalTables = false;
#endif
}
        
TableComposer::~TableComposer() {

}


#define INTERSECT_THRESHOLD 1

bool isPointWithinBox(const double (&inPoint)[2], const double (&inBox)[4]) {
    return inPoint[0] >= inBox[0] - INTERSECT_THRESHOLD &&
            inPoint[0] <= inBox[2] + INTERSECT_THRESHOLD &&
            inPoint[1] >= inBox[1] - INTERSECT_THRESHOLD &&
            inPoint[1] <= inBox[3] + INTERSECT_THRESHOLD;
}

bool HorizontalIntersectsWithVertical(const ParsedLinePlacement& inHorizontalLine, const ParsedLinePlacement& inVerticalLine, const double (&inScopeBox)[4]) {
    // should be forming a cross. so horizontal lines X coordinates should be surrounding vertical line X coordinate,
    // and horizontal line Y coordinate should be surrounded by vertical line Y coordinates
    bool doIntersect =  inHorizontalLine.globalPointOne[0] - inHorizontalLine.effectiveLineWidth[0]/2 <= inVerticalLine.globalPointOne[0] + inVerticalLine.effectiveLineWidth[0]/2  + INTERSECT_THRESHOLD &&
        inHorizontalLine.globalPointTwo[0] + inHorizontalLine.effectiveLineWidth[0]/2 >= inVerticalLine.globalPointOne[0] - inVerticalLine.effectiveLineWidth[0]/2 - INTERSECT_THRESHOLD &&
        inVerticalLine.globalPointTwo[1] - inVerticalLine.effectiveLineWidth[1]/2 <= inHorizontalLine.globalPointOne[1] + inHorizontalLine.effectiveLineWidth[1]/2 + INTERSECT_THRESHOLD &&
        inVerticalLine.globalPointOne[1] + inVerticalLine.effectiveLineWidth[1]/2 >= inHorizontalLine.globalPointOne[1] - inHorizontalLine.effectiveLineWidth[1]/2 - INTERSECT_THRESHOLD;

    if(!doIntersect)
        return false;

    // in addition to just checking if they intersect also make sure that intersection point is within the scope box (within tollerance)
    // the intersection point should be the vertical line X with the horizontal line Y of course.
    double intersectionPoint[2] = {inVerticalLine.globalPointOne[0],inHorizontalLine.globalPointOne[1]};

    return isPointWithinBox(intersectionPoint, inScopeBox);
}

bool CompareHorizontalLines(const ParsedLinePlacement& a, const ParsedLinePlacement& b) {
    // sort top to bottom
    if(a.globalPointOne[1] == b.globalPointOne[1])
        // and then left to right
        return a.globalPointOne[0] < b.globalPointOne[0];
    
    return a.globalPointOne[1] > b.globalPointOne[1];

}

bool CompareVerticalLines(const ParsedLinePlacement& a, const ParsedLinePlacement& b) {
    // sort left to right
    if(a.globalPointOne[0] == b.globalPointOne[0])
        // and then top to bottom
        return a.globalPointOne[1] > b.globalPointOne[1];
    
    return a.globalPointOne[0] < b.globalPointOne[0];
}


typedef GraphNode<const ParsedLinePlacement*> ParsedLinePlacementGraphNode;
typedef map<const ParsedLinePlacement*, ParsedLinePlacementGraphNode*> ParsedLinePlacementToParsedLinePlacementGraphNodeMap;
typedef set<ParsedLinePlacementGraphNode*> ParsedLinePlacementGraphNodeSet;


void CreateNodesForLinesList(
    const ParsedLinePlacementList& inList, 
    ParsedLinePlacementToParsedLinePlacementGraphNodeMap& refMap, 
    ParsedLinePlacementGraphNodeSet& refNodes
) {
    ParsedLinePlacementList::const_iterator it = inList.begin();
    for(; it != inList.end();++it) {
        const ParsedLinePlacement* item = &(*it);
        ParsedLinePlacementGraphNode* node = new ParsedLinePlacementGraphNode();
        node->value = item;
        refMap.insert(ParsedLinePlacementToParsedLinePlacementGraphNodeMap::value_type(item, node ));
        refNodes.insert(node);
    }
}

void CreateEdgesForLinesList(
    const ParsedLinePlacementList& inHorizontalList,
    const ParsedLinePlacementList& inVerticalList,
    const double (&inScopeBox)[4],
    ParsedLinePlacementToParsedLinePlacementGraphNodeMap& refMap
) {
    
    ParsedLinePlacementList::const_iterator itHorizontal = inHorizontalList.begin();
    
    for(; itHorizontal != inHorizontalList.end();++itHorizontal) {
        ParsedLinePlacementList::const_iterator itVertical = inVerticalList.begin();
        for(; itVertical != inVerticalList.end();++itVertical) {
            if(HorizontalIntersectsWithVertical(*itHorizontal, *itVertical, inScopeBox)) {
                ParsedLinePlacementGraphNode* horNode = refMap[&(*itHorizontal)];
                ParsedLinePlacementGraphNode* verNode = refMap[&(*itVertical)];
                horNode->neighbors.push_back(verNode);
                verNode->neighbors.push_back(horNode);
            }
        }
    }

}

LinesList DetermineTablesLines(const Lines& inLines, const double (&inScopeBox)[4]) {
    // So we need to determine which lines belong to which table
    // theoretically one could do that by just checking which horizontal lines intersect with which
    // vertical lines...then group all those vertical lines and horizontal lines that interesect with the same ones
    // and call it a day. however...given the existance of split cells (colspan > 1 for our html friends)
    // not all horizontal lines intersect with all vertical lines and so we need an approach that will support transitivity.
    // so - graphs. 
    // by repeatedly running BFS we can determine separate groups of lines that connect (transivitly intersect)...and if there
    // enough lines to form cells (>1 hor and >1 ver) we can consider this as a table. the outcome of this method is a lis of Lines
    // struct each forming such table
    ParsedLinePlacementToParsedLinePlacementGraphNodeMap linesToNodes;
    ParsedLinePlacementGraphNodeSet unvisitedNodes;
    LinesList result;

    // build graph
    CreateNodesForLinesList(inLines.horizontalLines, linesToNodes, unvisitedNodes);
    CreateNodesForLinesList(inLines.verticalLines, linesToNodes, unvisitedNodes);
    CreateEdgesForLinesList(inLines.horizontalLines, inLines.verticalLines, inScopeBox, linesToNodes);

    // while nodes set is not empty, determine subgraph of a candidate node and remove from node set, till
    // all nodes are accounted for, resulting in a tables lines list
    while(unvisitedNodes.size() > 0) {
        ParsedLinePlacementGraphNode* candidate =  *unvisitedNodes.begin();
        ParsedLinePlacementGraphNodeSet intersectionSubGraph = FindReachableNodes(candidate);
        
        Lines resultCandidate;
        ParsedLinePlacementGraphNodeSet::iterator it = intersectionSubGraph.begin();
        for(; it != intersectionSubGraph.end(); ++it) {
            if((*it)->value->isVertical)
                resultCandidate.verticalLines.push_back(*((*it)->value));
            else
                resultCandidate.horizontalLines.push_back(*((*it)->value));
        }

        if(resultCandidate.horizontalLines.size() > 1 && resultCandidate.verticalLines.size() > 1)
            result.push_back(resultCandidate);

        ParsedLinePlacementGraphNodeSet stillUnvisited;
        set_difference(
            unvisitedNodes.begin(), 
            unvisitedNodes.end(), 
            intersectionSubGraph.begin(), 
            intersectionSubGraph.end(), 
            inserter(stillUnvisited, stillUnvisited.begin())
        );
        unvisitedNodes = stillUnvisited;
       
    }

    // release graph nodes
    ParsedLinePlacementToParsedLinePlacementGraphNodeMap::iterator it = linesToNodes.begin();
    for(; it != linesToNodes.end();++it) {
        delete it->second;
    }
    return result;
}

typedef vector<ParsedLinePlacement> ParsedLinePlacementVector;


Lines ComputeCellInternalLines(
    const ParsedLinePlacementVector& insortedHorizontalLines, 
    const ParsedLinePlacementVector&  inSortedVerticalLines, 
    const double (&inCellBox)[4]
) { 
    Lines result;

    // This leaves much room for improvement...i got the lines sorted...can do binary search instead of iterating all.
    // rmmbr this is done on a PER CELL basis.
    // binary searching to make me feel better about this.


    // horizontal lines first
    int start = 0;
    int end = insortedHorizontalLines.size();

    // binary search the highest horizontal line that's lower than the box top
    while(end - start > 1) {
        int candidateIndex = start + floor((end - start)/2.0);

        if(insortedHorizontalLines[candidateIndex].globalPointOne[1] - insortedHorizontalLines[candidateIndex].effectiveLineWidth[1]  > inCellBox[3] + INTERSECT_THRESHOLD) {
            start = candidateIndex + 1;
        } else {
            end = candidateIndex;
        }
    }

    for(int i=start; i<insortedHorizontalLines.size(); ++i) {
        const ParsedLinePlacement& theLine = insortedHorizontalLines[i];

        // horizontal line is too low...can stop now
        if (theLine.globalPointOne[1] + theLine.effectiveLineWidth[1]  < inCellBox[1] - INTERSECT_THRESHOLD)
            break;

        // too much to the left
        if(theLine.globalPointTwo[0] + theLine.effectiveLineWidth[0] < inCellBox[0] - INTERSECT_THRESHOLD)
            continue;

        // too much to the right
        if(theLine.globalPointOne[0] - theLine.effectiveLineWidth[0] > inCellBox[2] + INTERSECT_THRESHOLD)
            continue;

        // just right...put it in
        result.horizontalLines.push_back(theLine);
    }

    // now for vertical lines
    start = 0;
    end = inSortedVerticalLines.size();

    // binary search the leftest vertical line that's righter than the box left
    while(end - start > 1) {
        int candidateIndex = start + floor((end - start)/2.0);

        if(inSortedVerticalLines[candidateIndex].globalPointOne[0] + inSortedVerticalLines[candidateIndex].effectiveLineWidth[0] < inCellBox[0] - INTERSECT_THRESHOLD) {
            start = candidateIndex + 1;
        } else {
            end = candidateIndex;
        }
    }    

    for(int i=start; i<inSortedVerticalLines.size(); ++i) {
        const ParsedLinePlacement& theLine = inSortedVerticalLines[i];

        // too much to the right, can stop now
        if(theLine.globalPointOne[0] - theLine.effectiveLineWidth[0] > inCellBox[2] + INTERSECT_THRESHOLD)
            break;

        // too high
        if(theLine.globalPointTwo[1] - theLine.effectiveLineWidth[1] > inCellBox[3] + INTERSECT_THRESHOLD)
            continue;

        // too low
        if(theLine.globalPointOne[1] + theLine.effectiveLineWidth[1] < inCellBox[1] - INTERSECT_THRESHOLD)
            continue;

        // just right...put it in
        result.verticalLines.push_back(theLine);
    }

    return result;
}

bool AreLinesEqual(const ParsedLinePlacement& inA, const ParsedLinePlacement& inB) {
    // this should be enough
    return inA.globalPointOne[0] == inB.globalPointOne[0] &&
            inA.globalPointOne[1] == inB.globalPointOne[1] &&
            inA.globalPointTwo[0] == inB.globalPointTwo[0] &&
            inA.globalPointTwo[1] == inB.globalPointTwo[1] &&
            inA.effectiveLineWidth[0] == inB.effectiveLineWidth[0] &&
            inA.effectiveLineWidth[1] == inB.effectiveLineWidth[1];
}


Result<Table> CreateTable(const Lines& inLines, const double (&inScopeBox)[4], bool inShouldParseInternalTables) {
    Table result;

    ParsedLinePlacementVector sortedHorizontalLines(inLines.horizontalLines.begin(), inLines.horizontalLines.end());
    sort(sortedHorizontalLines.begin(), sortedHorizontalLines.end(), CompareHorizontalLines);
    for(size_t i=sortedHorizontalLines.size()-1;i>0;--i) {
        // if y of later line + its width is higher than y of earlier line, check if their x's intersect. Then this pretty surely means that this is not actually
        // a table line, but rather some overlay drawing. ignore the new line
        if(
            sortedHorizontalLines[i].globalPointOne[1] + sortedHorizontalLines[i].effectiveLineWidth[1] >= sortedHorizontalLines[i-1].globalPointOne[1] &&
            sortedHorizontalLines[i-1].globalPointTwo[0] >= sortedHorizontalLines[i].globalPointOne[0] &&
            sortedHorizontalLines[i].globalPointTwo[0] >= sortedHorizontalLines[i-1].globalPointOne[0]
        ) {
            sortedHorizontalLines.erase(sortedHorizontalLines.begin() + i);
            continue;
        }


        if(
            sortedHorizontalLines[i].globalPointOne[1] == sortedHorizontalLines[i-1].globalPointOne[1] && 
            sortedHorizontalLines[i].effectiveLineWidth[0] == sortedHorizontalLines[i-1].effectiveLineWidth[0] &&
            sortedHorizontalLines[i].effectiveLineWidth[1] == sortedHorizontalLines[i-1].effectiveLineWidth[1] &&
            sortedHorizontalLines[i].globalPointOne[0] >= sortedHorizontalLines[i-1].globalPointOne[0] &&
            sortedHorizontalLines[i].globalPointTwo[0] >= sortedHorizontalLines[i-1].globalPointTwo[0] &&
            sortedHorizontalLines[i].globalPointTwo[0] + sortedHorizontalLines[i].effectiveLineWidth[0] >= sortedHorizontalLines[i-1].globalPointOne[0] - INTERSECT_THRESHOLD
        ) {
            // if y of both this and earlier line is the same and x's are close (less or equal to width diff) and line widths are the same then it's probably intended
            // that those are 2 segments of the same line. merge them.
            sortedHorizontalLines[i-1].globalPointTwo[0] = sortedHorizontalLines[i].globalPointTwo[0];
            sortedHorizontalLines.erase(sortedHorizontalLines.begin() + i);
            continue;
        }          
    }
    ParsedLinePlacementVector sortedVerticalLines(inLines.verticalLines.begin(), inLines.verticalLines.end());
    sort(sortedVerticalLines.begin(), sortedVerticalLines.end(), CompareVerticalLines);

    for(size_t i=sortedVerticalLines.size()-1;i>0;--i) {
        if(
            sortedVerticalLines[i].globalPointOne[0] - sortedVerticalLines[i].effectiveLineWidth[0] <= sortedVerticalLines[i-1].globalPointOne[0] &&
            sortedVerticalLines[i-1].globalPointOne[1] >= sortedVerticalLines[i].globalPointTwo[1] &&
            sortedVerticalLines[i].globalPointOne[1] >= sortedVerticalLines[i-1].globalPointTwo[1]
        ) {
            // if x of later line - its width is leftier than x of earlier line, check if their y's intersect. Then this pretty surely means that this is not actually
            // a table line, but rather some overlay drawing. ignore the new line
            sortedVerticalLines.erase(sortedVerticalLines.begin() + i);
            continue;
        }

        if(
            sortedVerticalLines[i].globalPointOne[0] == sortedVerticalLines[i-1].globalPointOne[0] && 
            sortedVerticalLines[i].effectiveLineWidth[0] == sortedVerticalLines[i-1].effectiveLineWidth[0] &&
            sortedVerticalLines[i].effectiveLineWidth[1] == sortedVerticalLines[i-1].effectiveLineWidth[1] &&
            sortedVerticalLines[i].globalPointOne[1] <= sortedVerticalLines[i-1].globalPointOne[1] &&
            sortedVerticalLines[i].globalPointTwo[1] <= sortedVerticalLines[i-1].globalPointTwo[1] &&
            sortedVerticalLines[i].globalPointOne[1] + sortedVerticalLines[i].effectiveLineWidth[1] >= sortedVerticalLines[i-1].globalPointTwo[1] - INTERSECT_THRESHOLD
        ) {
            // if x of both this and earlier line is the same and y's are close (less or equal to width diff) and line widths are the same then it's probably intended
            // that those are 2 segments of the same line. merge them.
            sortedVerticalLines[i-1].globalPointTwo[1] = sortedVerticalLines[i].globalPointTwo[1];
            sortedVerticalLines.erase(sortedVerticalLines.begin() + i);
            continue;
        }
    }

    ParsedLinePlacement leftVertical = sortedVerticalLines.front();
    ParsedLinePlacement rightVertical = sortedVerticalLines.back();

    ParsedLinePlacementVector rowLines;
    ParsedLinePlacementVector::iterator it = sortedHorizontalLines.begin();
    for(; it != sortedHorizontalLines.end(); ++it) {
        // Determine which horizontal lines are row lines. those are lines that stretch from left to right. we'll use pairs
        // of them to form row objects

        if(!HorizontalIntersectsWithVertical(*it, leftVertical, inScopeBox))
            continue;

        if(!HorizontalIntersectsWithVertical(*it, rightVertical, inScopeBox)) {
            continue;
        }

        rowLines.push_back(*it);
    }

    if(rowLines.size() == 0)
        return Result<Table>(); // no rows. ignore

    // Create row objects in the table based on the computed list. For each also compute its cells
    it = rowLines.begin();
    ParsedLinePlacement currentTop = *it;
    ++it;
    for(;it != rowLines.end(); ++it) {
        CellInRowVector cells;
        
        ParsedLinePlacementVector::iterator itCols = sortedVerticalLines.begin();
        ParsedLinePlacementVector cellLines;
        for(; itCols != sortedVerticalLines.end(); ++itCols) {
            // compute Cells by filtering vertical lines that intersect with both top and bottom row lines
            if(!HorizontalIntersectsWithVertical(currentTop, *itCols, inScopeBox))
                continue;

            if(!HorizontalIntersectsWithVertical(*it, *itCols, inScopeBox))
                continue;

            cellLines.push_back(*itCols);
        }

        if(cellLines.size() == 0)
            continue; // empty row with no cells. ignore

        ParsedLinePlacementVector::iterator itCell = cellLines.begin();
        ParsedLinePlacement currentLeft = *itCell;
        ++itCell;
        for(; itCell != cellLines.end(); ++itCell) {
            CellInRow cellInRow(
                currentLeft,
                *itCell,
                1, // initial value, computation below
                ParsedTextPlacementList(), // will be computed later
                NULL // will be computed later
            );
            cells.push_back(cellInRow);
            currentLeft = *itCell;
        }

        // create row with provided cells, top and bottom lines
        Row row = {
            currentTop,
            *it,
            cells
        };
        result.rows.push_back(row);

        currentTop = *it;
    }

    // Make sure we got a table here. It needs to have more than one row and one col...otherwise its not a table...it's a rectangle
    if(result.rows.size() == 0 || (result.rows.size() == 1 && result.rows.front().cells.size() == 1))
        return Result<Table>();

    // Compute col spans for each row cells based on the last line columns
    RowVector::reverse_iterator itRowsRev = result.rows.rbegin();
    Row& sampleRow = *itRowsRev;
    ++itRowsRev;
    for(; itRowsRev != result.rows.rend(); ++itRowsRev) {
        if(itRowsRev->cells.size() >= sampleRow.cells.size())
            continue; // should probaly only be equal...not more (at least i guess that's what we're expecting)

        // k. less cols than last line cells. means some cells take up multiple cols. figure out using cells width
        CellInRowVector::iterator itSampleRowCells = sampleRow.cells.begin();
        CellInRowVector::iterator itCurrentRowCells = itRowsRev->cells.begin();
        for(;itCurrentRowCells != itRowsRev->cells.end() && itSampleRowCells != sampleRow.cells.end(); ++itCurrentRowCells, ++itSampleRowCells) {
            while(itCurrentRowCells->rightLine.globalPointOne[0] > itSampleRowCells->rightLine.globalPointOne[0] + INTERSECT_THRESHOLD) {
                ++itSampleRowCells;
                ++itCurrentRowCells->colSpan;
            }
        }
    }

    if(inShouldParseInternalTables) {
        // Compute internal tables for each row cell. internal tables represent split cells where there are any.
        // I can consider making this more efficient by computing the internal lines earlier....
        // This computation is not very efficient iterating all table lines for each cell...i guess it's not a big deal
        // but there's room to improve here when i do want to
        RowVector::iterator itRows = result.rows.begin();
        for(; itRows != result.rows.end(); ++itRows) {
            CellInRowVector::iterator itCells = itRows->cells.begin();
            for(; itCells!=itRows->cells.end(); ++itCells) {
                // compoute lines that are internal to this cell. this will include the cell lines themselves
                double cellBox[4] = {
                    itCells->leftLine.globalPointOne[0] - itCells->leftLine.effectiveLineWidth[0]/2,
                    itRows->bottomLine.globalPointOne[1] - itRows->bottomLine.effectiveLineWidth[1]/2,
                    itCells->rightLine.globalPointOne[0] + itCells->rightLine.effectiveLineWidth[0]/2,
                    itRows->topLine.globalPointOne[1] + itRows->topLine.effectiveLineWidth[1]/2,
                };
                Lines linesInBox = ComputeCellInternalLines(sortedHorizontalLines, sortedVerticalLines, cellBox);
                
                if(linesInBox.horizontalLines.size() <= 2 && linesInBox.verticalLines.size() <= 2 ) {
                    // k no internal lines...just the 4 lines (or somehow...not even thems) of the cell
                    continue;
                }

                if(cellBox[0] == inScopeBox[0] &&
                    cellBox[1] == inScopeBox[1] &&
                    cellBox[2] == inScopeBox[2] &&
                    cellBox[3] == inScopeBox[3] &&
                    linesInBox.horizontalLines.size() == sortedHorizontalLines.size() &&
                    linesInBox.verticalLines.size() == sortedVerticalLines.size()) {
                        // for whatever reason (should probably debug if reaching here) there seems to be 
                        // a recursion here with the same entry conditions. don't.
                        continue; 
                    }

                LinesList internalTablesLinesList = DetermineTablesLines(linesInBox, cellBox);
                LinesList::iterator it = internalTablesLinesList.begin();
                for(; it != internalTablesLinesList.end(); ++it) {
                    Result<Table> tableResult = CreateTable(*it, cellBox, inShouldParseInternalTables);
                    if(tableResult.IsOK() && AreLinesEqual(tableResult.GetValue().rows.front().topLine, itRows->topLine)) {
                        // got internal table! if it is indeed an internal table it should have the cell lines as boundaries...so just check one
                        itCells->internalTable = new Table(tableResult.GetValue());
                    }
                }            
            }
        }
    }


    return Result<Table>(result);
}

bool AttachTextToContainerTableCell(const ParsedTextPlacement& inText, Table& refTable) {
    // check if in horizontal range
    if(refTable.rows.front().topLine.globalPointOne[1] < inText.globalBbox[1])
        return false;
    if(refTable.rows.back().bottomLine.globalPointTwo[1] > inText.globalBbox[3])
        return false;
    

    // find row, check according to text box top and row top
    int start = 0;
    int end = refTable.rows.size();

    while(end - start > 1) {
        int candidateIndex = start + floor((end - start)/2.0);

        if(refTable.rows[candidateIndex].topLine.globalPointOne[1] < inText.globalBbox[1]) {
            end = candidateIndex;
        } else {
            start = candidateIndex;
        }
    }

    // start should have the row index now
    Row& textRow = refTable.rows[start];
    
    if(textRow.cells.front().leftLine.globalPointOne[0] > inText.globalBbox[2])
        return false;
    if(textRow.cells.back().rightLine.globalPointTwo[0] < inText.globalBbox[0])
        return false;    

    // find cells
    start = 0;
    end = textRow.cells.size();

    while(end - start > 1) {
        int candidateIndex = start + floor((end - start)/2.0);

        if(textRow.cells[candidateIndex].leftLine.globalPointTwo[0] > inText.globalBbox[2]) {
            end = candidateIndex;
        } else {
            start = candidateIndex;
        }
    }

    // start should have the cell index now
    textRow.cells[start].textPlacements.push_back(inText);

    // cell got internal table? attempt to attach to it too (no need to report back)
    if(textRow.cells[start].internalTable)
        AttachTextToContainerTableCell(inText,*textRow.cells[start].internalTable);

    return true;

}

TableList TableComposer::ComposeTables(const Lines& inLines, const ParsedTextPlacementList& inTextPlacements, const double (&inScopeBox)[4]) {
    TableList tables; 

    // in each page
    
    // determine groups of lines that form tables (groups of lines with intersection relatinships that have more than 1 horizontal line and 1 vertical line)
    LinesList tablesLinesList = DetermineTablesLines(inLines, inScopeBox);

    // from each group of lines create a table objects. the creation process determines rows, and in each rows - cells (which implictly defines columns)
    LinesList::iterator it = tablesLinesList.begin();
    for(; it != tablesLinesList.end(); ++it) {
        Result<Table> tableResult = CreateTable(*it, inScopeBox, shouldParseInternalTables);
        if(tableResult.IsOK())
            tables.push_back(tableResult.GetValue());
    }

    // now for each text find the right table for it - if any - and place it in the right cell
    ParsedTextPlacementList::const_iterator itText = inTextPlacements.begin();
    for(; itText != inTextPlacements.end(); ++itText) {
        TableList::iterator itTables = tables.begin(); 
        for(; itTables != tables.end(); ++itTables) {
            if(AttachTextToContainerTableCell(*itText, *itTables))
                break; // found the right cell...can stop the search now
        }

    }

    return tables;

}