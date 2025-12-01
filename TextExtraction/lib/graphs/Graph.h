#pragma once

#include "Queue.h"
#include <list>
#include <set>

template <typename T>
struct GraphNode {
    T value;
    std::vector<GraphNode<T> *> neighbors;
};

/**
 * A BFS implementation to figure out which nodes can be reached from a source node.
 * For bidirectional graphs this will result in all the subgraph.
 * It's kinda funny but I didn't expect using this thing outside of uni and studying for
 * Google interviews. but then here it is - i'm using this to figure out which lines belong
 * to which table, accounting for split cells. unbelievable.
*/
template <typename T>
std::set<GraphNode<T> *> FindReachableNodes(GraphNode<T>* inSource) {
    std::set<GraphNode<T> *> visited;
    Queue<GraphNode<T> *> visitQueue;

    if(!inSource)
        return visited;

    visitQueue.Enqueue(inSource);

    while(!visitQueue.IsEmpty()) {
        GraphNode<T> *visitedNode = visitQueue.Dequeue().GetValue(); // just checked it's not empty...so should be fine
        if(visited.find(visitedNode) != visited.end())
            continue; // visited already, continue

        visited.insert(visitedNode);
        typename std::vector<GraphNode<T> *>::iterator it = visitedNode->neighbors.begin();
        for(;it != visitedNode->neighbors.end();++it)
            visitQueue.Enqueue(*it);
    }

    return visited;
}
