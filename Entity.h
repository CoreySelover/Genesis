
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

class Entity : public ManagedObject {
public:

    Entity(Game* game, int x, int y, bool canMove);

    virtual void update() {}

    virtual void draw() {}

    // Getters

    sf::Vector2f getPosition();

    bool canMove();

    // Setters

    /* Returns true if this Entity can move (and has had its position changed)
     * Returns false if this Entity can't move (m_xPosition is unchanged)
     */
    bool setPosition(float x, float y);

    bool setPosition(sf::Vector2f pos);

    void setMove(bool canMove);

protected:

    // Movement related

    sf::Vector2f m_position;

    bool m_canMove;
};
#endif // ENTITY_H

