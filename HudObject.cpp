
// Copyright 2018 Corey Selover

#include "HudObject.h"

#include "Game.h"
#include "Texture.h"
#include "Player.h"

HudObject::HudObject(Game* game,
                     std::string fileName,
                     sf::IntRect textureRect,
                     int x,
                     int y,
                     int quadrant,
                     bool visibleAtStart = true)
    : ManagedObject(game) {

    m_sprite.setTexture(m_game->addTexture(fileName)->get());
    // TODO - un-hard code this
    m_sprite.setOrigin(sf::Vector2f(0,0));
    m_sprite.setTextureRect(textureRect);
    m_textureRect = textureRect;

    switch(quadrant) {
        case 1:
            m_position = sf::Vector2f(m_game->windowCenter().x + m_game->windowSize().x / 2 - x,
                                      m_game->windowCenter().y - m_game->windowSize().y / 2 + y);
            break;
        case 2:
            m_position = sf::Vector2f(m_game->windowCenter().x - m_game->windowSize().x / 2 + x,
                                      m_game->windowCenter().y - m_game->windowSize().y / 2 + y);
            break;
        case 3:
            m_position = sf::Vector2f(m_game->windowCenter().x - m_game->windowSize().x / 2 + x,
                                      m_game->windowCenter().y + m_game->windowSize().y / 2 - y);
            break;
        case 4:
            m_position = sf::Vector2f(m_game->windowCenter().x + m_game->windowSize().x / 2 - x,
                                      m_game->windowCenter().y + m_game->windowSize().y / 2 - y);
            break;
        default:
            std::cout << "Invalid HudObject quadrant: " << quadrant << std::endl;
    }

    m_sprite.setPosition(m_position);

    m_visible = visibleAtStart;
}

void HudObject::update() {}

void HudObject::draw() {
    if(m_visible) m_game->draw(m_sprite);
}

sf::Vector2f HudObject::getPosition() {
    return m_position;
}

void HudObject::setPosition(sf::Vector2f pos) {
    m_position = pos;
}

// MANA_HUD_OBJECT

ManaHudObject::ManaHudObject(Game* game,
                     std::string fileName,
                     sf::IntRect textureRect,
                     int x,
                     int y,
                     int quadrant,
                     bool visibleAtStart = true)
    : HudObject(game, fileName, textureRect, x, y, quadrant, visibleAtStart) {

    m_meterSprite.setTexture(m_game->addTexture(fileName)->get());
    m_meterSprite.setOrigin(sf::Vector2f(0,0));
    m_meterSprite.setTextureRect(sf::IntRect(textureRect.left,
                                             textureRect.top + textureRect.height,
                                             textureRect.width,
                                             textureRect.height));
    m_meterSprite.setPosition(m_position);

    // Get player mana values.
    m_maxMana = static_cast<Player*>(m_game->entity("Player"))->maxMana();
    m_currentMana = static_cast<Player*>(m_game->entity("Player"))->currentMana();
    m_currentMeterPercentage = 100;
}

void ManaHudObject::update() {
    m_currentMana = static_cast<Player*>(m_game->entity("Player"))->currentMana();
    int manaPercentage = int(100 * m_currentMana / m_maxMana);

    m_meterSprite.setTextureRect(sf::IntRect(m_textureRect.left,
                                             m_textureRect.top + m_textureRect.height,
                                             int(m_textureRect.width * manaPercentage / 100),
                                             m_textureRect.height));
}

void ManaHudObject::draw() {
    HudObject::draw();
    if(m_visible) m_game->draw(m_meterSprite);
}

// AURA_HUD_OBJECT

AuraHudObject::AuraHudObject(Game* game,
                     std::string fileName,
                     sf::IntRect textureRect,
                     int x,
                     int y,
                     int quadrant,
                     bool visibleAtStart = true)
    : HudObject(game, fileName, textureRect, x, y, quadrant, visibleAtStart) {

    m_active = false;
}

void AuraHudObject::update() {
    if (m_active) {
        m_sprite.setTextureRect(sf::IntRect(m_textureRect.left,
                                m_textureRect.top + m_textureRect.height,
                                m_textureRect.width,
                                m_textureRect.height));
    }
    else {
        m_sprite.setTextureRect(m_textureRect);
    }
}

void AuraHudObject::toggle() {
    m_active = !m_active;
}

bool AuraHudObject::active() const {
    return m_active;
}
