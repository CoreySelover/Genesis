
// Copyright 2018 Corey Selover

#include "Console.h"

#include "Game.h"
#include "Texture.h"

Console::Console(Game* game)
    : m_game(game),
      m_visible(false) {

    m_sprite.setTexture(m_game->addTexture("resources/textures/TEXTURE_CONSOLE.png", true)->get());
    m_sprite.setOrigin(sf::Vector2f(0,0));
    m_sprite.setTextureRect(sf::IntRect(0, 0, m_game->windowSize().x, 100));
    m_sprite.setPosition(0, 0);

    m_arial.loadFromFile("resources/fonts/arial.ttf");

    m_text.setPosition(20, 20);
    m_text.setFont(m_arial);
    m_text.setFillColor(sf::Color::Black);
    m_text.setCharacterSize(20);
    m_text.setStyle(sf::Text::Bold);
}

void Console::handle(sf::Event event) {
    if(event.type == sf::Event::TextEntered) {
        // Backspace
        if(event.text.unicode == 8) {
            if (m_stream.str().size() > 0) {
                std::string newStr = m_stream.str();
                newStr.resize(newStr.size()-1);
                m_stream.str("");
                m_stream << newStr;
            }
        }
        else if(event.text.unicode != 96) {
            m_stream << char(event.text.unicode);
        }
    }
}

void Console::update() {
    m_text.setString(m_stream.str());
}

void Console::draw() {
    if(!m_visible) return;

    m_game->draw(m_sprite);
    m_game->draw(m_text);
}

void Console::toggle() { m_visible = !m_visible; }

bool Console::active() { return m_visible; }

Console::~Console() {}
