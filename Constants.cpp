
// Copyright 2018 Corey Selover

#include "Constants.h"

sf::Vector2f Constants::mapCenter() {
    return sf::Vector2f(Constants::MAP_WIDTH * Constants::TILE_WIDTH / 2,
                        Constants::MAP_HEIGHT * Constants::TILE_HEIGHT / 2);
}
