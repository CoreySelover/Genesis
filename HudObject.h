
// Copyright 2018 Corey Selover

#ifndef HUD_OBJECT
#define HUD_OBJECT

#include "Manager.h"

// External libraries
#include <SFML/Graphics.hpp>

class Game;

class HudObject : public ManagedObject {
public:
    HudObject(Game* game,
              std::string fileName,
              sf::IntRect textureRect,
              int x,
              int y,
              bool visibleAtStart);

    virtual void update();

    virtual void draw();

    // Getters

    sf::Vector2f getPosition();

    // Setters

    void setPosition(sf::Vector2f pos);

    void setTextureRect(sf::IntRect textureRect);

protected:

    sf::Sprite  m_sprite;

    sf::IntRect m_textureRect;

    sf::Vector2f m_position;

    bool m_visible;
};

#endif // HUD_OBJECT
