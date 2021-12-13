/*
 * TDDD86 Trailblazer
 * This file declares the functions you will write in this assignment.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Author: Marty Stepp
 * Slight modifications by Tommy Farnqvist
 */

#ifndef _trailblazer_h
#define _trailblazer_h

#include <vector>
#include "BasicGraph.h"
#include "pqueue.h"

vector<Node*> depthFirstSearch(BasicGraph& graph, Node* start, Node* end);
vector<Node*> breadthFirstSearch(BasicGraph& graph, Node* start, Node* end);
/**
 * An implementation of Dijkstras algorithm.
 *
 * @param graph A BasicGraph.
 * @param start The node the method will start the search on.
 * @param end The node the method will end the search on.
 * @return A vector of all the nodes between (and including) start and end.
 */
vector<Node*> dijkstrasAlgorithm(BasicGraph& graph, Node* start, Node* end);
vector<Node*> aStar(BasicGraph& graph, Node* start, Node* end);
/**
 *
 * @param graph A BasicGraph.
 * @param currentNode The node that is currently being updated.
 * @param queue A priority queue.
 * @param visited A vector containing all visited nodes.
 */
void setNodesInfinity(BasicGraph& graph, Vertex* currentNode, PriorityQueue<Vertex*>& queue, Set<Node*> visited);

#endif
