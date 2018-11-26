
// Copyright 2018 Corey Selover

#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"

class Game;

enum MonsterType {
    MONSTER_TERROR
};

class Monster : public Entity {
public:
    Monster(Game* game, int x, int y, bool canMove, int damage, int maxHealth);

    virtual void update();

    virtual void draw();

protected:

    int m_damage;
    int m_maxHealth;
    int m_currentHealth;

};

class Terror : public Monster {
public:
    Terror(std::string name, Game* game, int x, int y, bool canMove);

    void update();
};

#endif // MONSTER_H
