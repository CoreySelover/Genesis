
// Copyright 2018 Corey Selover

#include "Screen.h"

Screen::Screen(Game* game)
    : ManagedObject(game) {
    m_consoleVisible = false;
}

void Screen::turnConsoleOn() {
    m_consoleVisible = true;
}

void Screen::turnConsoleOff() {
    m_consoleVisible = false;
}
