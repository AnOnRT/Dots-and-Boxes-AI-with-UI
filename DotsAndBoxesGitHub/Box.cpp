
#include "Box.h"

Box::Box() : owner(' ') {}

bool Box::isCompleted() const {
    return left.isDrawn && top.isDrawn && right.isDrawn && bottom.isDrawn;
}

char Box::getOwner() const {
    return owner;
}