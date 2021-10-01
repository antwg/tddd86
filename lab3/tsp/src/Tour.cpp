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
    // TODO: write this member
}

void Tour::show()
{
    if (firstNodePointer == nullptr){
        return;
    }
    Node* curr = firstNodePointer;
    cout << curr->point.toString() << endl;
    curr = curr->next;
    while (curr != firstNodePointer){
        cout << curr->point.toString() << endl;
        curr = curr->next;
    }
}

void Tour::draw(QGraphicsScene *scene)
{
    if (firstNodePointer == nullptr){
        return;
    }
    Node* curr = firstNodePointer;
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
    if (firstNodePointer == nullptr){
        return size;
    }
    Node* curr = firstNodePointer;
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
    totalDistance += curr->point.distanceTo(curr->next->point);
    curr = curr->next;

    while (curr != firstNodePointer){
        totalDistance += curr->point.distanceTo(curr->next->point);
        curr = curr->next;
    }
    return totalDistance;
}

void Tour::insertNearest(Point p)
{
    if (firstNodePointer == nullptr){
        firstNodePointer = new Node(p, nullptr);
        firstNodePointer->next = firstNodePointer;
        return;
    }
    Node* nearestNodePtr = nullptr;
    int shortestDist = INT_MAX;

    Node* curr = firstNodePointer;

    int currDist = p.distanceTo(curr->point);
    if (currDist < shortestDist) {
        shortestDist = currDist;
        nearestNodePtr = curr;
    }

    curr = curr->next;
    while (curr != firstNodePointer){
        int currDist = p.distanceTo(curr->point);
        if (currDist < shortestDist) {
            shortestDist = currDist;
            nearestNodePtr = curr;
        }
        curr = curr->next;
    }

    Node* temp = nearestNodePtr->next;
    nearestNodePtr->next = new Node(p, temp);
}

void Tour::insertSmallest(Point p)
{
    if (firstNodePointer == nullptr){
        firstNodePointer = new Node(p, nullptr);
        firstNodePointer->next = firstNodePointer;
        return;
    }
    Node* smallestNodePtr = nullptr;
    int smallestIncrease = INT_MAX;

    Node* curr = firstNodePointer;

    int currIncrease = curr->point.distanceTo(p) +
            p.distanceTo(curr->next->point) -
            curr->point.distanceTo(curr->next->point);

    if (currIncrease < smallestIncrease) {
        smallestIncrease = currIncrease;
        smallestNodePtr = curr;
    }

    curr = curr->next;
    while (curr != firstNodePointer){
        int currIncrease = curr->point.distanceTo(p) +
                p.distanceTo(curr->next->point) -
                curr->point.distanceTo(curr->next->point);

        if (currIncrease < smallestIncrease) {
            smallestIncrease = currIncrease;
            smallestNodePtr = curr;
        }
        curr = curr->next;
    }

    Node* temp = smallestNodePtr->next;
    smallestNodePtr->next = new Node(p, temp);
}
