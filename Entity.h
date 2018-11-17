
// Copyright 2018 Corey Selover
#ifndef ENTITY_H
#define ENTITY_H

/* An Entity is any game object that occupies physical space, or is in some way
 * interact-able.  For example, the Player, a powerup, a hidden event, etc.
 */

// External libraries
#include <SFML/Graphics.hpp>

#include "Manager.h"

class Game;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ULEFT,
    URIGHT,
    DLEFT,
    DRIGHT
};

class Entity : public ManagedObject {
public:

    Entity(Game* game, int x, int y, bool canMove);

    virtual void initializeSprite() = 0;

    virtual void update();

    virtual void draw();

    // Getters

    sf::Vector2f getPixelPosition();

    sf::Vector2i getTilePosition();

    bool canMove();

    // Setters

    /* Returns true if this Entity can move (and has had its position changed)
     * Returns false if this Entity can't move (m_pixelPosition is unchanged)
     */
    bool setPixelPosition(float x, float y);

    bool setPixelPosition(sf::Vector2f pos);

    bool setTilePosition(int x, int y);

    bool setTilePosition(sf::Vector2i pos);

    void setMove(bool canMove);

protected:

    sf::Sprite m_sprite;

    // Movement related

    sf::Vector2f m_pixelPosition;

    sf::Vector2i m_tilePosition;

    bool m_canMove;
};
#endif // ENTITY_H

