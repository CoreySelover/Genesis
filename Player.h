
// Copyright 2018 Corey Selover
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player: public Entity {
    public:
        Player(int x, int y, bool canMove);
};

#endif // PLAYER_H
