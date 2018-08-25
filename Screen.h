
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
    Screen(Game* game, bool active = false);

    virtual void update();

    virtual void draw() {}

    virtual void processInput(sf::Event event) {}

    ~Screen() {}

    void deactivate();

    void activate();

    // Timekeeping

    void restartClock();

    sf::Time elapsedTime();

private:
    bool m_active;

    // Clock

    sf::Clock m_currentTime;
};
#endif // SCREEN_H
