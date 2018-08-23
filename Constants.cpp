
// Copyright 2018 Corey Selover

#include "Constants.h"

sf::Vector2i Constants::mapCenterAsPixels() {
    return sf::Vector2i(Constants::MAP_WIDTH * Constants::TILE_WIDTH / 2,
                        Constants::MAP_HEIGHT * Constants::TILE_HEIGHT / 2);
}

sf::Vector2i Constants::mapCenterAsCoordinates() {
    return sf::Vector2i(Constants::MAP_WIDTH / 2,
                        Constants::MAP_HEIGHT / 2);
}
