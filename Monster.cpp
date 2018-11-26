
// Copyright 2018 Corey Selover

#include "Monster.h"
#include "Game.h"

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
}

void Monster::draw() {
    Entity::draw();
}

//////////////////////////////////////////////////////////////////////////////////
//                              Terror                                          //
//////////////////////////////////////////////////////////////////////////////////

Terror::Terror(std::string name, Game* game, int x, int y, bool canMove)
    // TODO - load these numbers instead of hardcoding them
    : Monster(game, x, y, canMove, 1, 3) {

    initializeSprite("resources/textures/TEXTURE_TERROR.png", sf::Vector2f(32,32));
}

void Terror::update() {
    Monster::update();
}
