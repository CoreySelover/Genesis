
// Copyright 2018 Corey Selover

#ifndef MANAGER_H
#define MANAGER_H

#include <map>
#include <iostream>

class Game;
class Entity;
class Texture;
class Screen;

class ManagedObject {
public:
    ManagedObject(Game* game);

    virtual void update() = 0;

    virtual void draw() = 0;

    virtual ~ManagedObject() {}

    virtual void print() {}

    // Access to other ManagedObjects.

    Entity* entity(std::string name);

    Texture* texture(std::string name);

    Screen* screen(std::string name);

    // ManagedObjects can create Textures
    Texture* addTexture(std::string filePath);

private:
    Game* m_game;
};

class Manager {
public:
    Manager();

    void update();

    void draw();

    ~Manager();

    // Management

    /* Adds a ManagedObject to the manager.
     * If the object is already managed, return it
     * rather than replacing.
     */
    ManagedObject* add(std::string name, ManagedObject* object);

    void del(std::string name);

    ManagedObject* get(std::string name);

    void print(bool verbose = false);

private:
    std::map<std::string, ManagedObject*> m_managed;

};
#endif // MANAGER_H
