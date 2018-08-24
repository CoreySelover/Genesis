
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

    void toggle();

    bool active();

    ~Console();

private:
    Game* m_game;

    sf::Sprite m_sprite;

    sf::Text m_text;

    bool m_visible;
};

#endif // CONSOLE_H
