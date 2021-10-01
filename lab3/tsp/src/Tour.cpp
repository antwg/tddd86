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

Tour::Tour(Point a, Point b, Point c, Point d)
{
    Node* node4 = new Node(d, nullptr);
    Node* node3 = new Node(c, node4);
    Node* node2 = new Node(b, node3);
    Node* node1 = new Node(a, node2);
    node4->next = node1;

    firstNodePointer = node1;
}

Tour::~Tour()
{
    // TODO: write this member
}

void Tour::show()
{   // If there are no nodes, abort
    if (firstNodePointer == nullptr){
        return;
    }
    Node* curr = firstNodePointer;

    // Special case for only first node
    cout << curr->point.toString() << endl;
    curr = curr->next;

    // Loop until first node found. Print every loop
    while (curr != firstNodePointer){
        cout << curr->point.toString() << endl;
        curr = curr->next;
    }

    // TODO: write this member
}

void Tour::draw(QGraphicsScene *scene)
{   // If there are no nodes, abort
    if (firstNodePointer == nullptr){
        return;
    }
    Node* curr = firstNodePointer;

    // Special case for first node
    curr->point.drawTo(curr->next->point, scene);
    curr = curr->next;

    // Loop over all nodes until first node is found. Draw lines every loop.
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
    // TODO: write this member
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
