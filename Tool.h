
// Copyright 2018 Corey Selover

#ifndef TOOL_H
#define TOOL_H

// External libraries
#include <SFML/Graphics.hpp>

class Tool {
public:
    static const float ALLOWED_POSITION_DISCREPANCY = 2;

    static float distance(sf::Vector2f pos1, sf::Vector2f pos2);

    static sf::Vector2i pixelsToTile(sf::Vector2f pixelPosition, int tileWidth = 128, int tileHeight = 128);

    static sf::Vector2f tileToPixels(sf::Vector2i tilePosition, int tileWidth = 128, int tileHeight = 128);
};

#endif // TOOL_H


