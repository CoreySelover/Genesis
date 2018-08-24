
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
    m_text.setFont(m_arial);
    m_text.setPosition(20, 20);
    m_text.setFillColor(sf::Color::Black);
    m_text.setCharacterSize(20);
    m_text.setStyle(sf::Text::Bold);
}

void Console::handle(sf::Event event) {
    if(event.type == sf::Event::TextEntered) {
        // Just leave this here and enable/disable as needed.
        //std::cout << event.text.unicode << std::endl;

        // Enter
        if(event.text.unicode == 13) {
            interpret();
        }
        // Backspace
        if(event.text.unicode == 8) {
            if (m_stream.str().size() > 0) {
                std::string newStr = m_stream.str();
                newStr.resize(newStr.size()-1);
                m_stream.str("");
                m_stream << newStr;
            }
        }
        else if(event.text.unicode != 96 && event.text.unicode != 13) {
            m_stream << char(event.text.unicode);
        }
    }
}

void Console::interpret() {
    std::string first = m_stream.str().substr(0, m_stream.str().find("="));
    std::string second = m_stream.str().substr(m_stream.str().find("=") + 1);

    // No = sign found, therefore look for command names.
    if(first.compare(second) == 0) {
        m_game->runCommand(first);
    }
    else {
        // If an assignment is prepended by $, we intend to save it to disk.
        if(first.substr(0,1).compare("$") == 0) {
            m_game->assignGameValue(first.substr(1), second, true);
        }
        else {
            m_game->assignGameValue(first, second, false);
        }
    }
}

void Console::displayError(std::string message, std::string error) {
    m_visible = true;
    m_stream.str("");
    m_stream << message << " " << error;
}

void Console::clean() {
    m_stream.str("");
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
