
// Copyright 2018 Corey Selover
#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:

    Entity(int x, int y, bool canMove);

    // Getters

    int getX();

    int getY();

    bool canMove();

    // Setters

    /* Returns true if this Entity can move (and has had its position changed)
     * Returns false if this Entity can't move (m_xPosition is unchanged)
     */
    bool setX(int x);

    bool setY(int y);

    void setMove(bool canMove);

private:

    // Movement related

    int m_xPosition;

    int m_yPosition;

    bool m_canMove;
};
#endif // ENTITY_H

