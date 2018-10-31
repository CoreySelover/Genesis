
// Copyright 2018 Corey Selover

#ifndef HUD_OBJECT
#define HUD_OBJECT

#include "Manager.h"

// External libraries
#include <SFML/Graphics.hpp>

class Game;

class HudObject : public ManagedObject {
public:
    /*
     * x and y are used in conjunction with quadrant (think quadrants of a graph)
     * to determine where the HudObject will appear.
     * x and y basically count as "how much room from the corner should I have?"
     */
    HudObject(Game* game,
              std::string fileName,
              sf::IntRect textureRect,
              int x,
              int y,
              int quadrant,
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

class ManaHudObject : public HudObject {
public:
    ManaHudObject(Game* game,
              std::string fileName,
              sf::IntRect textureRect,
              int x,
              int y,
              int quadrant,
              bool visibleAtStart);

    void update();

    void draw();

private:
    sf::Sprite m_meterSprite;

    int m_currentMana;

    int m_currentMeterPercentage;

    int m_maxMana;
};

class AuraHudObject : public HudObject {
public:
    AuraHudObject(Game* game,
              std::string fileName,
              sf::IntRect textureRect,
              int x,
              int y,
              int quadrant,
              bool visibleAtStart);

    void update();

    void toggle();

    bool active() const;

private:
    bool m_active;
};

#endif // HUD_OBJECT
