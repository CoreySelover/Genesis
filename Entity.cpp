
// Copyright 2018 Corey Selover

#include "Entity.h"
#include "Tool.h"

Entity::Entity(Game* game, int x, int y, bool canMove = true)
    : ManagedObject(game) {

    m_pixelPosition = sf::Vector2f(x, y);

    m_tilePosition = Tool::pixelsToTile(m_pixelPosition);

    m_canMove = canMove;
}

void Entity::update() {
    m_tilePosition = Tool::pixelsToTile(m_pixelPosition);
}

sf::Vector2f Entity::getPixelPosition() {
    return m_pixelPosition;
}

bool Entity::setPixelPosition(float x, float y) {
    if(m_canMove) {
        m_pixelPosition = sf::Vector2f(x, y);
        return true;
    }

    return false;
}

bool Entity::setPixelPosition(sf::Vector2f pos) {
    if(m_canMove) {
        m_pixelPosition = pos;
        return true;
    }

    return false;
}

bool Entity::canMove() {

    return m_canMove;
}

void Entity::setMove(bool canMove) {

    m_canMove = canMove;
}
