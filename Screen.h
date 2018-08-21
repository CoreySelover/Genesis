
// Copyright 2018 Corey Selover

#ifndef SCREEN_H
#define SCREEN_H

/* A Screen is an overall picture of everything to be displayed at one time.
 * Examples of screens include: Maps, menus, splash images, etc.
 */

 // External libraries
#include <SFML/Graphics.hpp>

#include "Manager.h"

class Game;

class Screen : public ManagedObject {
public:
    Screen(Game* game);

    virtual void update() {}

    virtual void draw() {}

    ~Screen() {}

private:
    sf::Sprite m_sprite;

    Game* m_game;
};
#endif // SCREEN_H