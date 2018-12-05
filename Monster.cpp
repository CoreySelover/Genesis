
// Copyright 2018 Corey Selover

#include "Monster.h"
#include "Game.h"
#include "Tile.h"

Monster::Monster(Game* game, int x, int y, bool canMove, int damage, int maxHealth)
    : Entity(game, x, y, canMove) {

    m_damage        = damage;
    m_maxHealth     = maxHealth;
    m_currentHealth = maxHealth;
}

// TODO - since these two methods aren't actually doing anything... are they necessary?
// Do they even need to be declared?  Or can a subclass of Monster implement them without them
// listed in Monster?
void Monster::update() {
    Entity::update();

    // Time to move
    if(m_game->tileByPixels(m_pixelPosition.x, m_pixelPosition.y)->getType() == TileType::TILE_BLANK) {
        moveToNextTarget();
    }
    else if (m_damageClock.getElapsedTime().asSeconds() >= 1) {
        m_game->tileByPixels(m_pixelPosition.x, m_pixelPosition.y)->decreaseHealth(m_damage);
        m_damageClock.restart();
    }
}

void Monster::draw() {
    Entity::draw();
}

void Monster::move(Direction direction) {
    switch(direction) {
        case UP:
            m_pixelPosition.y -= m_maxSpeed;
            break;
        case DOWN:
            m_pixelPosition.y += m_maxSpeed;
            break;
        case LEFT:
            m_pixelPosition.x -= m_maxSpeed;
            break;
        case RIGHT:
            m_pixelPosition.x += m_maxSpeed;
            break;
        case ULEFT:
            m_pixelPosition.x -= m_maxSpeed / sqrt(2);
            m_pixelPosition.y -= m_maxSpeed / sqrt(2);
            break;
        case URIGHT:
            m_pixelPosition.x += m_maxSpeed / sqrt(2);
            m_pixelPosition.y -= m_maxSpeed / sqrt(2);
            break;
        case DLEFT:
            m_pixelPosition.x -= m_maxSpeed / sqrt(2);
            m_pixelPosition.y += m_maxSpeed / sqrt(2);
            break;
        case DRIGHT:
            m_pixelPosition.x += m_maxSpeed / sqrt(2);
            m_pixelPosition.y += m_maxSpeed / sqrt(2);
            break;
    }
}

//////////////////////////////////////////////////////////////////////////////////
//                              Terror                                          //
//////////////////////////////////////////////////////////////////////////////////

Terror::Terror(std::string name, Game* game, int x, int y, bool canMove)
    // TODO - load these numbers instead of hardcoding them
    : Monster(game, x, y, canMove, 1, 3) {

    initializeSprite("resources/textures/TEXTURE_TERROR.png", sf::Vector2f(32,32));
    randomizeDirection();
    m_maxSpeed = 5;
}

void Terror::randomizeDirection() {
    m_direction = static_cast<Direction>(rand() % 8);
}

void Terror::update() {
    Monster::update();
}

void Terror::moveToNextTarget() {
    Monster::move(m_direction);
}
