#include "TableComposer.h"

#include "../graphs/Graph.h"

#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

TableComposer::TableComposer() {

}
        
TableComposer::~TableComposer() {

}


#define INTERSECT_THRESHOLD 1

bool HorizontalIntersectsWithVertical(const ParsedLinePlacement& inHorizontalLine, const ParsedLinePlacement& inVerticalLine) {
    // should be forming a cross. so horizontal lines X coordinates should be surrounding vertical line X coordinate,
    // and horizontal line Y coordinate should be surrounded by vertical line Y coordinates
    return 
        inHorizontalLine.globalPointOne[0] - inHorizontalLine.effectiveLineWidth[0]/2 <= inVerticalLine.globalPointOne[0] + inVerticalLine.effectiveLineWidth[0]/2  + INTERSECT_THRESHOLD &&
        inHorizontalLine.globalPointTwo[0] + inHorizontalLine.effectiveLineWidth[0]/2 >= inVerticalLine.globalPointOne[0] - inVerticalLine.effectiveLineWidth[0]/2 - INTERSECT_THRESHOLD &&
        inVerticalLine.globalPointTwo[1] - inVerticalLine.effectiveLineWidth[1]/2 <= inHorizontalLine.globalPointOne[1] + inHorizontalLine.effectiveLineWidth[1]/2 + INTERSECT_THRESHOLD &&
        inVerticalLine.globalPointOne[1] + inVerticalLine.effectiveLineWidth[1]/2 >= inHorizontalLine.globalPointOne[1] - inHorizontalLine.effectiveLineWidth[1]/2 - INTERSECT_THRESHOLD;
}

bool CompareHorizontalLines(const ParsedLinePlacement& a, const ParsedLinePlacement& b) {
    // sort top to bottom
    return a.globalPointOne[1] > b.globalPointOne[1];
}

bool CompareVerticalLines(const ParsedLinePlacement& a, const ParsedLinePlacement& b) {
    // sort left to right
    return a.globalPointOne[0] < b.globalPointOne[0];
}


typedef vector<ParsedLinePlacement> ParsedLinePlacementVector;

Table CreateTable(const Lines& inLines) {
    Table result;

    ParsedLinePlacementVector sortedHoriztonalLines(inLines.horizontalLines.begin(), inLines.horizontalLines.end());
    sort(sortedHoriztonalLines.begin(), sortedHoriztonalLines.end(), CompareHorizontalLines);
    ParsedLinePlacementVector sortedVerticalLines(inLines.verticalLines.begin(), inLines.verticalLines.end());
    sort(sortedVerticalLines.begin(), sortedVerticalLines.end(), CompareVerticalLines);

    ParsedLinePlacement leftVertical = sortedVerticalLines.front();
    ParsedLinePlacement rightVertical = sortedVerticalLines.back();

    // determine which horizontal lines are row lines. those are lines that stretch from left to right. we'll use pairs
    // of them to form row objects
    ParsedLinePlacementVector rowLines;
    ParsedLinePlacementVector::iterator it = sortedHoriztonalLines.begin();
    for(; it != sortedHoriztonalLines.end(); ++it) {
        if(HorizontalIntersectsWithVertical(*it, leftVertical) && HorizontalIntersectsWithVertical(*it, rightVertical)) {
            rowLines.push_back(*it);
        }
    }

    // create row objects in the table. each will have a cell
    it = rowLines.begin();
    ParsedLinePlacement currentTop = *it;
    ++it;
    for(;it != rowLines.end(); ++it) {
        CellInRowVector cells;
        
        // compute Cells by filtering vertical lines that intersect with both top and bottom row lines
        ParsedLinePlacementVector::iterator itCols = sortedVerticalLines.begin();
        ParsedLinePlacementVector cellLines;
        for(; itCols != sortedVerticalLines.end(); ++itCols) {
            if(HorizontalIntersectsWithVertical(currentTop, *itCols) && HorizontalIntersectsWithVertical(*it, *itCols)) {
                cellLines.push_back(*itCols);
            }
        }

        ParsedLinePlacementVector::iterator itCell = cellLines.begin();
        ParsedLinePlacement currentLeft = *itCell;
        ++itCell;
        for(; itCell != cellLines.end(); ++itCell) {
            CellInRow cellInRow = {
                currentLeft,
                *itCell,
                1, // initial value, computation below
                ParsedTextPlacementList() // will be computed later
            };
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

    // last thing. considering this is a table determine how many cols each cell wrap
    // we'll do cols per the last line, which if there are data rows in the table is sure is one
    RowVector::reverse_iterator itRev = result.rows.rbegin();
    Row& sampleRow = *itRev;
    ++itRev;
    for(; itRev != result.rows.rend(); ++itRev) {
        if(itRev->cells.size() >= sampleRow.cells.size())
            continue; // should probaly only be equal...not more (at least i guess that's what we're expecting)

        // k. less cols than last line cells. means some cells take up multiple cols. figure out using cells width
        CellInRowVector::iterator itSampleRowCells = sampleRow.cells.begin();
        CellInRowVector::iterator itCurrentRowCells = itRev->cells.begin();
        for(;itCurrentRowCells != itRev->cells.end() && itSampleRowCells != sampleRow.cells.end(); ++itCurrentRowCells, ++itSampleRowCells) {
            while(itCurrentRowCells->rightLine.globalPointOne[0] > itSampleRowCells->rightLine.globalPointOne[0] + INTERSECT_THRESHOLD) {
                ++itSampleRowCells;
                ++itCurrentRowCells->colSpan;
            }
        }
    }

    /**
     * A note about what's not currently done here about split cells. A header row could span multiple columns and may internally be split
     * to rows and columns to describe the columns. One can easily reuse the table composer with what lines are determined to be intersecting
     * within a single cell (those lines that are NOT row lines, for instance, and columns that don't intersect top to bottom) to recreate that
     * internal split structure. At this point in time im keeping this out of scope, because at this point in time i'm extracting table to CSV
     * which does not allow for such header splitting. This is more relevant to more complex spreadsheets like excel, google sheets and mac numbers
     * which i'm not trying to export to...cause the format is too complex for such a 80-20 implementation like we're trying to do here.
     * BUT if at any point i will change to export to something that can handle split cells....then this parsing would make sense and the cells data
     * may be enhanced. It souldn't be that big a difference, just that a table cell might contain a Table as an alternative to just text placements
     * (or in addition to still make it simple to export to CSV).
     */

    return result;
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

    return true;

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
    ParsedLinePlacementToParsedLinePlacementGraphNodeMap& refMap
) {
    
    ParsedLinePlacementList::const_iterator itHorizontal = inHorizontalList.begin();
    
    for(; itHorizontal != inHorizontalList.end();++itHorizontal) {
        ParsedLinePlacementList::const_iterator itVertical = inVerticalList.begin();
        for(; itVertical != inVerticalList.end();++itVertical) {
            if(HorizontalIntersectsWithVertical(*itHorizontal, *itVertical)) {
                ParsedLinePlacementGraphNode* horNode = refMap[&(*itHorizontal)];
                ParsedLinePlacementGraphNode* verNode = refMap[&(*itVertical)];
                horNode->neighbors.push_back(verNode);
                verNode->neighbors.push_back(horNode);
            }
        }
    }

}

LinesList DetermineTablesLines(const Lines& inLines) {
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
    CreateEdgesForLinesList(inLines.horizontalLines, inLines.verticalLines, linesToNodes);

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

TableList TableComposer::ComposeTables(const Lines& inLines, const ParsedTextPlacementList& inTextPlacements) {
    TableList tables; 

    // in each page
    
    // determine groups of lines that form tables (groups of lines with intersection relatinships that have more than 1 horizontal line and 1 vertical line)
    LinesList tablesLinesList = DetermineTablesLines(inLines);

    // from each group of lines create a table objects. the creation process determines rows, and in each rows - cells (which implictly defines columns)
    LinesList::iterator it = tablesLinesList.begin();
    for(; it != tablesLinesList.end(); ++it) {
        tables.push_back(CreateTable(*it));
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