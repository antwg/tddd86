// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Node* firstNodePointer = nullptr;

Tour::Tour()
{
    // TODO: write this member
}

Tour::~Tour()
{
    if (firstNodePointer == nullptr){
        return;
    }

    Node* currNodePtr = firstNodePointer;
    Node* nextNodePtr = firstNodePointer->next;

    while (nextNodePtr != firstNodePointer){
        delete &currNodePtr;
        currNodePtr = nextNodePtr;
        nextNodePtr = currNodePtr->next;
    }
    delete &currNodePtr;
}

void Tour::show()
{   // If there are no nodes, return
    if (firstNodePointer == nullptr){
        return;
    }
    Node* curr = firstNodePointer;

    // Special case for first node
    cout << curr->point.toString() << endl;
    curr = curr->next;

    while (curr != firstNodePointer){
        cout << curr->point.toString() << endl;
        curr = curr->next;
    }
}

void Tour::draw(QGraphicsScene *scene)
{   // If there are no nodes, return
    if (firstNodePointer == nullptr){
        return;
    }
    Node* curr = firstNodePointer;

    // Special case for first node
    curr->point.drawTo(curr->next->point, scene);
    curr = curr->next;

    while (curr != firstNodePointer){
        curr->point.drawTo(curr->next->point, scene);
        curr = curr->next;
    }
}

int Tour::size()
{
    int size = 0;

    // If there are no nodes, return 0
    if (firstNodePointer == nullptr){
        return size;
    }
    Node* curr = firstNodePointer;

    // Special case for first node
    size++;
    curr = curr->next;

    while (curr != firstNodePointer){
        size++;
        curr = curr->next;
    }
    return size;
}

double Tour::distance()
{
    double totalDistance = 0;
    Node* curr = firstNodePointer;

    // Special case for first node
    totalDistance += curr->point.distanceTo(curr->next->point);
    curr = curr->next;

    while (curr != firstNodePointer){
        totalDistance += curr->point.distanceTo(curr->next->point);
        curr = curr->next;
    }
    return totalDistance;
}

void Tour::insertNearest(Point p)
{   // If there are no nodes, create a new node that points to itself.
    if (firstNodePointer == nullptr){
        firstNodePointer = new Node(p, nullptr);
        firstNodePointer->next = firstNodePointer;
        return;
    }

    // Start at first node
    Node* curr = firstNodePointer;
    int currDist = p.distanceTo(curr->point);
    int shortestDist = currDist;
    Node* nearestNodePtr = curr;
    curr = curr->next;

    // Compare with all other nodes
    while (curr != firstNodePointer){
        currDist = p.distanceTo(curr->point);
        if (currDist < shortestDist) {
            shortestDist = currDist;
            nearestNodePtr = curr;
        }
        curr = curr->next;
    }

    // Insert new node after nearest node
    Node* temp = nearestNodePtr->next;
    nearestNodePtr->next = new Node(p, temp);
}

int getCurrentIncrease(Node* curr, const Point& p){ // New dist(CP+PN) - old dist(CN), c=current, n=next, p=new point
    return curr->point.distanceTo(p) +
            p.distanceTo(curr->next->point) -
            curr->point.distanceTo(curr->next->point);
}

void Tour::insertSmallest(Point p)
{   // If there are no nodes, create a new node that points to itself.
    if (firstNodePointer == nullptr){
        firstNodePointer = new Node(p, nullptr);
        firstNodePointer->next = firstNodePointer;
        return;
    }

    // Start at first node
    Node* curr = firstNodePointer;
    int currIncrease = getCurrentIncrease(curr, p);
    int smallestIncrease = currIncrease;
    Node* smallestNodePtr = curr;

    curr = curr->next;

    // Compare with all other nodes
    while (curr != firstNodePointer){
        int currIncrease = getCurrentIncrease(curr, p);
        if (currIncrease < smallestIncrease) {
            smallestIncrease = currIncrease;
            smallestNodePtr = curr;
        }
        curr = curr->next;
    }

    // Insert new node after smallest node
    Node* temp = smallestNodePtr->next;
    smallestNodePtr->next = new Node(p, temp);
}
