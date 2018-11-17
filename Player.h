
// Copyright 2018 Corey Selover

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

#include <SFML/Graphics.hpp>

class Game;

class Player: public Entity {
public:
    Player(Game* game, int x, int y, bool canMove);

    void initializeSprite();

    void update();

    // Input and movement

    void processInput(sf::Event event);

    void walk(Direction direction);

    bool createAt(sf::Vector2f coords);

    // Getters and Setters

    int maxMana() const;

    int currentMana() const;

    int auraRadius() const;

    void setAuraType(int auraType);

private:

    int m_maxSpeed;
    int m_auraRadius;
    int m_auraType;
    int m_maxMana;
    int m_currentMana;
    int m_manaRechargeRate;
    std::map<int, int> m_manaCost;
    sf::Clock m_manaTimer;

    bool m_left;
    bool m_right;
    bool m_up;
    bool m_down;
    bool m_mouseDown;
};

#endif // PLAYER_H
