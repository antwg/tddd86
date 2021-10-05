/*
 * TDDD86 TSP
 * Benjamin Sundvall - bensu844
 * Anton Wegeström - antwe841
 *
 * This file contains the declaration of the Tour structure.
 * See Tour.cpp for implementation of each member.
 */

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:

    Tour();
    Tour(Point a, Point b, Point c, Point d);
    ~Tour();

    /*
     * Prints the points that makes up the tour.
     */
    void show();

    /*
     * Draws the tour onto the given QGraphicsScene.
     */
    void draw(QGraphicsScene* scene);

    /*
     * Returns the number of nodes in the tour.
     */
    int size();

    /*
     * Returns the total distance of the tour.
     */
    double distance();

    /*
     * Inserts a new node in the tour after the nearest already existing point.
     */
    void insertNearest(Point p);

    /*
     * Inserts a new node in the tour in the position that would cause the smallest increase in total distance.
     */
    void insertSmallest(Point p);

private:
    /*
     * Returns the increase in distance that would be caused by inserting a new node after the given node.
     */
    int getCurrentIncrease(Node* curr, const Point& p);
};

#endif // TOUR_H
