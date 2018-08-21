
// Copyright 2018 Corey Selover

#ifndef MANAGER_H
#define MANAGER_H

#include <map>
#include <iostream>

class ManagedObject {
public:
    ManagedObject() {}

    virtual void update() = 0;

    virtual void draw() = 0;

    virtual ~ManagedObject() {}

    virtual void print() {}
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

    void print(bool verbose);

private:
    std::map<std::string, ManagedObject*> m_managed;

};
#endif // MANAGER_H
