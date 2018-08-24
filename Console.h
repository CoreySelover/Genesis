
// Copyright 2018 Corey Selover

#ifndef CONSOLE_H
#define CONSOLE_H

// External libs
#include <SFML/Graphics.hpp>
#include <sstream>

class Game;

class Console {
public:
    Console(Game* game);

    void handle(sf::Event event);

    void update();

    void draw();

    void toggle();

    bool active();

    ~Console();

private:
    Game* m_game;

    sf::Sprite m_sprite;

    std::stringstream m_stream;

    sf::Text m_text;

    sf::Font m_arial;

    bool m_visible;
};

#endif // CONSOLE_H
