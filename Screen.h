
// Copyright 2018 Corey Selover

#ifndef SCREEN_H
#define SCREEN_H

/* A Screen is an overall picture of everything to be displayed at one time.
 * Examples of screens include: Maps, menus, splash images, etc.
 */
class Screen : public ManagedObject {
public:
    Screen() {}

    virtual void update() {}

    virtual void draw() {}
};
#endif // SCREEN_H
