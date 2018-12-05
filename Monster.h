
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

    // This method moves the monster in a given direction.
    virtual void move(Direction direction);

    /* This method ensures that any subclass defines a behavior for when to move
     * and which direction when it is not currently on a valid tile.
     */
    virtual void moveToNextTarget() = 0;

protected:

    int m_damage;
    int m_maxHealth;
    int m_currentHealth;
    int m_maxSpeed;

    sf::Clock m_damageClock;

};

class Terror : public Monster {
public:
    Terror(std::string name, Game* game, int x, int y, bool canMove);

    void randomizeDirection();

    void update();

    void moveToNextTarget();

private:

    Direction m_direction;
};

#endif // MONSTER_H
