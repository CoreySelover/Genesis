
// Copyright 2018 Corey Selover

#include "Entity.h"

Entity::Entity(int x, int y, bool canMove = true) {

    setX(x);
    setY(y);

    m_canMove = canMove;
}

int Entity::getX() {

    return m_xPosition;
}

int Entity::getY() {

    return m_yPosition;
}

bool Entity::canMove() {

    return m_canMove;
}

bool Entity::setX(int x) {

    if (canMove()) {
        m_xPosition = x;
        return true;
    }

    return false;
}

bool Entity::setY(int y) {

    if (canMove()) {
        m_yPosition = y;
        return true;
    }

    return false;
}

void Entity::setMove(bool canMove) {

    m_canMove = canMove;
}
