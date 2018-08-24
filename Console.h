
// Copyright 2018 Corey Selover

#ifndef CONSOLE_H
#define CONSOLE_H

// External libs
#include <SFML/Graphics.hpp>

class Game;

class Console {
public:
    Console(Game* game);

    void update();

    void draw();

    ~Console();

private:
    Game* m_game;

    sf::Sprite m_sprite;

    sf::Text m_text;
};

#endif // CONSOLE_H
