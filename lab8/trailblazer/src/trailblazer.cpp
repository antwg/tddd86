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

vector<Node*> BFS(BasicGraph& graph, Vertex* currentNode, Vertex* targetNode, Vector<Vertex*> path){
    /*
    // Previsit
    currentNode->visited = true;
    currentNode->setColor(GREEN);
    Set<Arc*> outgoingEdges = currentNode->arcs;

    for(Arc* edgeToNeighbor : outgoingEdges){
        Vertex* neighborNode = edgeToNeighbor->finish;

        if (neighborNode == targetNode) {
            //vector<Node*> toReturn = {currentNode, neighborNode};     // Return the path from current to last (trivial)
            //return toReturn;    // return [currentMode, targetNode]
        } else if (!neighborNode->visited) {
            //vector<Node*> res = DFS(graph, neighborNode, targetNode);  // Recursive step
            //if(!res.empty()){   // If a path to the target node exists...
                //vector<Node*> toReturn = res;                   // Ugly
                //toReturn.insert(toReturn.begin(), currentNode);
                //return toReturn;    // ... return [currentNode] + res
            }
        }
    }

    return BFS(graph, )
    // No path has been found from currentNode to targetNode
    vector<Node*> toReturn = {};
    return toReturn;
    */
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* startNode, Vertex* targetNode) {
    graph.resetData();
    queue<vector<Vertex*>> searchQueue;
    vector<Vertex*> path = {startNode};
    searchQueue.push(path);

    while(!searchQueue.empty()){
        vector<Vertex*> path = searchQueue.front();     // continue on the next potential path
        searchQueue.pop();

        Vertex* currentNode = path.back();
        currentNode->visited = true;
        currentNode->setColor(GREEN);

        // check if current path leads to the target node
        if(currentNode == targetNode){
            return path;
        }

        // queue exploration of all neigbors of the current node
        for(Arc* edgeToNeighbor : currentNode->arcs){
            Vertex* neighbor = edgeToNeighbor->finish;
            if(!neighbor->visited){
                vector<Vertex*> newPath = path;
                newPath.push_back(neighbor);
                neighbor->setColor(YELLOW);
                searchQueue.push(newPath);
            }
        }
    }
    path.clear();   // No path to target found
    return path;
}

void setNodesInfinity(BasicGraph& graph, Vertex* currentNode, PriorityQueue<Vertex*>& queue, Set<Node*> visited = {}){
    // Set cost of currentNode to infinity
    visited.add(currentNode);
    queue.enqueue(currentNode, POSITIVE_INFINITY);
    currentNode->cost = POSITIVE_INFINITY;
    // For all neighbors
    Set<Arc*> outgoingEdges = currentNode->arcs;
    for(Arc* edgeToNeighbor : outgoingEdges){
        Vertex* neighborNode = edgeToNeighbor->finish;
        // If not visited, recurse
        if (!visited.contains(neighborNode)){
            setNodesInfinity(graph, neighborNode, queue, visited);
        }
    }
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // Setup
    graph.resetData();
    vector<Vertex*> path;
    PriorityQueue<Vertex*> priorityQueue;
    setNodesInfinity(graph, start, priorityQueue);

    // Begin with start node
    start->cost = 0;
    priorityQueue.changePriority(start, 0);
    start->visited = true;

    while (!priorityQueue.isEmpty()){
        // Pick shortest distance to start
        Node* shortestDistNode = priorityQueue.dequeue();
        shortestDistNode->setColor(GREEN);

        for (Arc* edgeToNeighbor : shortestDistNode->arcs){
            Vertex* neighborNode = edgeToNeighbor->finish;
            // If neighbor is end node
            if (neighborNode == end){
                // Update node
                neighborNode->previous = shortestDistNode;
                path.push_back(neighborNode);
                neighborNode->setColor(GREEN);
                // Add all previous nodes to path
                while (neighborNode != start) {
                    path.push_back(neighborNode->previous);
                    neighborNode = neighborNode->previous;
                }
                // Reverse and return
                std::reverse(path.begin(), path.end());
                return path;
            }
            else if (!neighborNode->visited){
                // Update node
                neighborNode->previous = shortestDistNode;
                neighborNode->visited = true;
                neighborNode->setColor(YELLOW);

                // If new path to node is shorter than current, update
                double newCost = shortestDistNode->cost + edgeToNeighbor->cost;
                if (newCost < neighborNode->cost) {
                    neighborNode->cost = newCost;
                    priorityQueue.changePriority(neighborNode, newCost);
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
    setNodesInfinity(graph, start, priorityQueue);

    // Begin with start node
    start->cost = 0;
    priorityQueue.changePriority(start, 0);
    start->visited = true;

    while (!priorityQueue.isEmpty()){
        // Pick shortest distance to start
        Node* shortestDistNode = priorityQueue.dequeue();
        shortestDistNode->setColor(GREEN);

        for (Arc* edgeToNeighbor : shortestDistNode->arcs){
            Vertex* neighborNode = edgeToNeighbor->finish;
            // If neighbor is end node
            if (neighborNode == end){
                // Update node
                neighborNode->previous = shortestDistNode;
                path.push_back(neighborNode);
                neighborNode->setColor(GREEN);
                // Add all previous nodes to path
                while (neighborNode != start) {
                    path.push_back(neighborNode->previous);
                    neighborNode = neighborNode->previous;
                }
                // Reverse and return
                std::reverse(path.begin(), path.end());
                return path;
            }
            else if (!neighborNode->visited){
                // Update node
                neighborNode->previous = shortestDistNode;
                neighborNode->visited = true;
                neighborNode->setColor(YELLOW);

                // If new path to node is shorter than current, update
                double newCost = shortestDistNode->cost + edgeToNeighbor->cost;
                if (newCost < neighborNode->cost) {
                    neighborNode->cost = newCost;
                    priorityQueue.changePriority(neighborNode, newCost + neighborNode->heuristic(end));
                }
            }
        }
    }
    return path;
}
