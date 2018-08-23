
// Copyright 2018 Corey Selover

#ifndef CONSTANTS_H
#define CONSTANTS_H

// External libraries
#include <SFML/Graphics.hpp>

class Constants {
public:
    // Always 1 less than desired to account for array indexes
    static const int MAP_HEIGHT = 99;
    static const int MAP_WIDTH = 99;

    static const int TILE_WIDTH = 64;
    static const int TILE_HEIGHT = 64;

    static sf::Vector2f mapCenterAsPixels();
    static sf::Vector2i mapCenterAsCoordinates();
};

#endif // CONSTANTS_H
