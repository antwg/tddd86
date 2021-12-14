/*
 * This file contains implementations of 4 search algorithms:
 * DFS
 * BFS
 * Dijkstras
 * A*
 *
 * antwe841
 * bensu844
 */

#include "costs.h"
#include "trailblazer.h"
#include "pqueue.h"
#include <queue>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <set>
using namespace std;

vector<Node*> DFS(BasicGraph& graph, Vertex* currentNode, Vertex* targetNode){
    // Previsit
    currentNode->visited = true;
    currentNode->setColor(GREEN);
    Set<Arc*> outgoingEdges = currentNode->arcs;

    for(Arc* edgeToNeighbor : outgoingEdges){
        Vertex* neighborNode = edgeToNeighbor->finish;

        if (neighborNode == targetNode) {
            vector<Node*> toReturn = {currentNode, neighborNode};     // Return the path from current to last (trivial)
            return toReturn;    // return [currentMode, targetNode]
        } else if (!neighborNode->visited) {
            vector<Node*> res = DFS(graph, neighborNode, targetNode);  // Recursive step
            if(!res.empty()){   // If a path to the target node exists...
                vector<Node*> toReturn = res;                   // Ugly
                toReturn.insert(toReturn.begin(), currentNode);
                return toReturn;    // ... return [currentNode] + res
            }
        }
    }
    // No path has been found from currentNode to targetNode
    vector<Node*> toReturn = {};
    return toReturn;
}

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    return DFS(graph, start, end);
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* startNode, Vertex* targetNode) {
    graph.resetData();
    queue<Vertex*> searchQueue;
    vector<Vertex*> path;
    searchQueue.push(startNode);

    while(!searchQueue.empty()){
        // Queue startNode
        Vertex* currentNode = searchQueue.front();
        searchQueue.pop();
        currentNode->visited = true;
        currentNode->setColor(GREEN);

        if(currentNode == targetNode){
            // Update currentNode
            path.push_back(currentNode);
            currentNode->setColor(GREEN);
            // Add all predecesors to path
            while (currentNode != startNode) {
                path.push_back(currentNode->previous);
                currentNode = currentNode->previous;
            }
            return path;
        }

        // queue exploration of all neigbors of the current node
        for(Arc* edgeToNeighbor : currentNode->arcs){
            Vertex* neighbor = edgeToNeighbor->finish;
            if(!neighbor->visited){
                neighbor->visited = true;
                neighbor->previous = currentNode;
                searchQueue.push(neighbor);
                neighbor->setColor(YELLOW);
            }
        }
    }
    return path;
}

void setNodesInfinity(BasicGraph& graph, PriorityQueue<Vertex*>& queue){
    for (Node* node : graph.getVertexSet()){
        queue.enqueue(node, POSITIVE_INFINITY);
        node->cost = POSITIVE_INFINITY;
    }
}


vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // Setup
    graph.resetData();
    vector<Vertex*> path;
    PriorityQueue<Vertex*> priorityQueue;
    unordered_set<Node*> temp;
    setNodesInfinity(graph, priorityQueue);

    // Begin with start node
    start->cost = 0;
    priorityQueue.changePriority(start, 0);
    start->visited = true;

    while (!priorityQueue.isEmpty()){
        // Pick shortest distance to start
        Node* shortestDistNode = priorityQueue.dequeue();
        shortestDistNode->setColor(GREEN);

        if (shortestDistNode == end){
            // Update node
            path.push_back(shortestDistNode);
            // Add all previous nodes to path
            while (shortestDistNode != start) {
                path.push_back(shortestDistNode->previous);
                shortestDistNode = shortestDistNode->previous;
            }
            // Reverse and return
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (Arc* edgeToNeighbor : shortestDistNode->arcs){
            Vertex* neighborNode = edgeToNeighbor->finish;
            // If neighbor is end node

            double newCost = shortestDistNode->cost + edgeToNeighbor->cost;
            // If new cost lower, update cost
            if (newCost < neighborNode->cost){
                neighborNode->cost = newCost;
                neighborNode->previous = shortestDistNode;
                priorityQueue.changePriority(neighborNode, newCost);
                if (!neighborNode->visited){
                    // Update node
                    neighborNode->visited = true;
                    neighborNode->setColor(YELLOW);
                }
            }

        }
    }
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // Setup
    graph.resetData();
    vector<Vertex*> path;
    PriorityQueue<Vertex*> priorityQueue;
    unordered_set<Node*> temp;
    setNodesInfinity(graph, priorityQueue);

    // Begin with start node
    start->cost = 0;
    priorityQueue.changePriority(start, 0);
    start->visited = true;

    while (!priorityQueue.isEmpty()){
        // Pick shortest distance to start
        Node* shortestDistNode = priorityQueue.dequeue();
        shortestDistNode->setColor(GREEN);

        if (shortestDistNode == end){
            // Update node
            path.push_back(shortestDistNode);
            // Add all previous nodes to path
            while (shortestDistNode != start) {
                path.push_back(shortestDistNode->previous);
                shortestDistNode = shortestDistNode->previous;
            }
            // Reverse and return
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (Arc* edgeToNeighbor : shortestDistNode->arcs){
            Vertex* neighborNode = edgeToNeighbor->finish;
            // If neighbor is end node

            double newCost = shortestDistNode->cost + edgeToNeighbor->cost;
            // If new cost lower, update cost
            if (newCost < neighborNode->cost){
                neighborNode->cost = newCost;
                neighborNode->previous = shortestDistNode;
                priorityQueue.changePriority(neighborNode, newCost + neighborNode->heuristic(end));
                if (!neighborNode->visited){
                    // Update node
                    neighborNode->visited = true;
                    neighborNode->setColor(YELLOW);
                }
            }

        }
    }
    return path;
}
