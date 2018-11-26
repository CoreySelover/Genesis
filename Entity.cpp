
// Copyright 2018 Corey Selover

#include "Entity.h"
#include "Tool.h"
#include "Game.h"
#include "Texture.h"

Entity::Entity(Game* game, int x, int y, bool canMove = true)
    : ManagedObject(game) {

    m_pixelPosition = sf::Vector2f(x, y);

    m_tilePosition = Tool::pixelsToTile(m_pixelPosition, m_game->tileWidth(), m_game->tileHeight());

    m_canMove = canMove;
}

void Entity::initializeSprite(std::string texturePath, sf::Vector2f spriteOrigin) {
    m_sprite.setTexture(m_game->addTexture(texturePath)->get());
    m_sprite.setOrigin(spriteOrigin);
    centerSpriteInTile();
}

void Entity::centerSpriteInTile() {
    m_pixelPosition.x = m_pixelPosition.x + m_game->tileWidth() / 2;
    m_pixelPosition.y = m_pixelPosition.y + m_game->tileHeight() / 2;
}

void Entity::update() {
    m_tilePosition = Tool::pixelsToTile(m_pixelPosition, m_game->tileWidth(), m_game->tileHeight());

    // Sync sprite
    m_sprite.setPosition(m_pixelPosition);
}

void Entity::draw() {
    m_game->draw(m_sprite);
}

sf::Vector2f Entity::getPixelPosition() {
    return m_pixelPosition;
}

sf::Vector2i Entity::getTilePosition() {
    return m_tilePosition;
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

bool Entity::setTilePosition(int x, int y) {
    return setPixelPosition(Tool::tileToPixels(sf::Vector2i(x,y)));
}

bool Entity::setTilePosition(sf::Vector2i pos) {
    return setPixelPosition(Tool::tileToPixels(pos));
}

bool Entity::canMove() {

    return m_canMove;
}

void Entity::setMove(bool canMove) {

    m_canMove = canMove;
}
