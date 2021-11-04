/**
 * bensu844
 * antwe841
 *
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * A crashed version of Robot that can't move etc.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    Junk(const Point& p);

    Junk* clone() const;

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const;

    void moveTowards(const Unit&);

    void doCrash();

    bool justCrashed() const;

    bool canMove() const;
};

#endif // JUNK_H
