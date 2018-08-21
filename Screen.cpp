
// Copyright 2018 Corey Selover

#include "Screen.h"

Screen::Screen(Game* game) {
    m_game = game;
    m_consoleVisible = false;
}

void Screen::turnConsoleOn() {
    m_consoleVisible = true;
}

void Screen::turnConsoleOff() {
    m_consoleVisible = false;
}
