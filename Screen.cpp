
// Copyright 2018 Corey Selover

#include "Screen.h"

#include "Game.h"

Screen::Screen(Game* game, bool active)
    : ManagedObject(game) {
    m_active = active;
}

void Screen::update() {
    if(!m_active) {
        m_game->nextScreen();
    }
}

void Screen::deactivate() {
    m_active = false;
}

void Screen::activate() {
    m_active = true;
}

void Screen::restartClock() {
    m_currentTime.restart();
}

sf::Time Screen::elapsedTime() {
    return m_currentTime.getElapsedTime();
}
