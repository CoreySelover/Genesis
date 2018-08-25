
// Copyright 2018 Corey Selover
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

#include <SFML/Graphics.hpp>

class Game;

class Player: public Entity {
public:
    Player(Game* game, int x, int y, bool canMove);

    void update();

    void draw();

    // Input and movement

    void processInput(sf::Event event);

    void moveTo(sf::Vector2i coords);

private:
    // TODO - This should probably be in Entity or some other base class
    sf::Sprite m_sprite;

    sf::Vector2i m_targetLocation;

    int m_maxSpeed;
};

#endif // PLAYER_H
