
// Copyright 2018 Corey Selover

#include "Tool.h"

// External libs
#include <math.h>
#include <iostream>

float Tool::distance(sf::Vector2f pos1, sf::Vector2f pos2) {
    sf::Vector2f diffVector = pos1 - pos2;
    return sqrt(pow(diffVector.x, 2) + pow(diffVector.y, 2));
}

sf::Vector2i Tool::pixelsToTile(sf::Vector2f pixelPosition, int tileWidth, int tileHeight) {
    return sf::Vector2i(int(pixelPosition.x / tileWidth), int(pixelPosition.y / tileHeight));
}
