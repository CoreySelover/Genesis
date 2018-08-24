
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

private:
    sf::Sprite m_sprite;
};

#endif // PLAYER_H
