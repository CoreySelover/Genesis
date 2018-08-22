
// Copyright 2018 Corey Selover

#include "Screen.h"

#include "Game.h"

Screen::Screen(Game* game, bool active)
    : ManagedObject(game) {
    m_active = active;
    m_consoleVisible = false;
}

void Screen::update() {
    if(!m_active) {
        m_game->nextScreen();
    }
}

void Screen::turnConsoleOn() {
    m_consoleVisible = true;
}

void Screen::turnConsoleOff() {
    m_consoleVisible = false;
}

void Screen::deactivate() {
    m_active = false;
}

void Screen::activate() {
    m_active = true;
}
