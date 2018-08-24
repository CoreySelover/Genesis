
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
}

void Console::update() {}

void Console::draw() {
    if(!m_visible) return;

    m_game->draw(m_sprite);
    m_game->draw(m_text);
}

void Console::toggle() { m_visible = !m_visible; }

bool Console::active() { return m_visible; }

Console::~Console() {}
