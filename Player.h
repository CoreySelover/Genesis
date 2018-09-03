
// Copyright 2018 Corey Selover
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

#include <SFML/Graphics.hpp>

class Game;

enum AuraType {
    AURA_GRASS,
    AURA_FOREST,
    AURA_WATER,
    AURA_ROCK
};

class Player: public Entity {
public:
    Player(Game* game, int x, int y, bool canMove);

    void update();

    void draw();

    // Input and movement

    void processInput(sf::Event event);

    void walk(Direction direction);

    void createAt(sf::Vector2f coords);

    int auraRadius();

private:
    // TODO - This should probably be in Entity or some other base class
    sf::Sprite m_sprite;

    sf::Vector2f m_targetLocation;

    int m_maxSpeed;

    int m_auraRadius;
    AuraType m_auraType;

    bool m_left;
    bool m_right;
    bool m_up;
    bool m_down;
    bool m_mouseDown;
};

#endif // PLAYER_H
