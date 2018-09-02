
// Copyright 2018 Corey Selover

#include "Entity.h"

Entity::Entity(Game* game, int x, int y, bool canMove = true)
    : ManagedObject(game) {

    m_position = sf::Vector2f(x, y);

    m_canMove = canMove;
}

sf::Vector2f Entity::getPosition() {
    return m_position;
}

bool Entity::canMove() {

    return m_canMove;
}

bool Entity::setPosition(float x, float y) {
    if(m_canMove) {
        m_position = sf::Vector2f(x, y);
        return true;
    }

    return false;
}

bool Entity::setPosition(sf::Vector2f pos) {
    if(m_canMove) {
        m_position = pos;
        return true;
    }

    return false;
}

void Entity::setMove(bool canMove) {

    m_canMove = canMove;
}
