// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
// TODO: include any other headers you need; remove this comment
#include <queue>
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

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}
