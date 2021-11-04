/**
 * bensu844
 * antwe841
 *
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * A crashed version of Robot that can't move etc.
 */

#include "Junk.h"
#include "constants.h"


Junk::Junk(const Point& p): Robot(p){
    crashed = true;
}

Junk* Junk::clone() const{
    return new Junk{ *this };
}

void Junk::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(JUNK_COLOR));
}

void Junk::moveTowards(const Unit&){
    // Is not able to move
}

void Junk::doCrash(){
    // Has already crashed so it can't crash again
}


bool Junk::justCrashed() const {
    return false;
}

bool Junk::canMove() const{
        return false;

}
