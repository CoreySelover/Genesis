
// Copyright 2018 Corey Selover

#ifndef MANAGER_H
#define MANAGER_H

#include <map>
#include <iostream>

class Game;

class ManagedObject {
public:
    ManagedObject(Game* game);

    virtual void update() = 0;

    virtual void draw() = 0;

    virtual ~ManagedObject() {}

    virtual void print() {}

protected:
    // TODO - can we do better than friend classes?
    friend class Tile;

    Game* m_game;
};

class Manager {
public:
    Manager();

    void update();

    void draw();

    void shutdown();

    ~Manager();

    void print(bool verbose = false);

    // Management

    ManagedObject* add(std::string name, ManagedObject* object);

    void del(std::string name);

    ManagedObject* get(std::string name);

    std::string nextName(std::string nameBase);

private:
    std::map<std::string, ManagedObject*> m_managed;

    bool m_update;

    bool m_draw;

    std::map<std::string, unsigned int> m_objectNames;

};
#endif // MANAGER_H
