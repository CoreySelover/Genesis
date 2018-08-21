
// Copyright 2018 Corey Selover

#ifndef MANAGER_H
#define MANAGER_H

#include <map>
#include <iostream>

class ManagedObject {
public:
    ManagedObject() {}

    virtual void update() = 0;

    virtual void draw() {}
};

class Manager {
public:
    Manager();

    void update();

    void draw();

    ~Manager();

private:
    std::map<std::string, ManagedObject*> m_managed;

};
#endif // MANAGER_H
