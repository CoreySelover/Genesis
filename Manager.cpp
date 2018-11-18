
// Copyright 2018 Corey Selover

#include <sstream>

#include "Manager.h"

#include "Game.h"

//////////////////////////////////////
//        ManagedObject             //
//////////////////////////////////////

ManagedObject::ManagedObject(Game* game) {
    m_game = game;
}

//////////////////////////////////////
//            Manager               //
//////////////////////////////////////

Manager::Manager() {
    m_update = true;
    m_draw = true;
}

void Manager::print(bool verbose) {
    std::map<std::string, ManagedObject*>::iterator itr;
    for (itr = m_managed.begin(); itr != m_managed.end(); itr++) {
        std::cout << itr->first << std::endl;
        if(verbose) itr->second->print();
    }
}

void Manager::update() {
    if(!m_update) return;

    std::map<std::string, ManagedObject*>::iterator itr;
    for(itr = m_managed.begin(); itr != m_managed.end(); itr++) {
        itr->second->update();
    }
}

void Manager::draw() {
    if(!m_draw) return;

    std::map<std::string, ManagedObject*>::iterator itr;
    for(itr = m_managed.begin(); itr != m_managed.end(); itr++) {
        itr->second->draw();
    }
}

void Manager::shutdown() {
    m_update = false;
    m_draw = false;
}

Manager::~Manager() {
    std::map<std::string, ManagedObject*>::iterator itr;
    for(itr = m_managed.begin(); itr != m_managed.end(); itr++) {
        delete itr->second;
    }
    m_managed.clear();
}

ManagedObject* Manager::add(std::string name, ManagedObject* object) {
    if(m_managed.count(name)) {
        return m_managed[name];
    }
    else {
        m_managed[name] = object;
        return m_managed[name];
    }
}

void Manager::del(std::string name) {
    std::map<std::string, ManagedObject*>::iterator itr = m_managed.find(name);
    if (itr != m_managed.end()) {
        delete itr->second;
        m_managed.erase(itr);
    }
}

ManagedObject* Manager::get(std::string name) {
    try {
        if(!m_managed.count(name)) {
            throw name;
        }
        else {
            return m_managed[name];
        }
    }
    catch (std::string missingObject) {
        std::cout << "Object doesnt exist: " << missingObject << std::endl;
    }

    return NULL;
}

std::string Manager::nextName(std::string nameBase) {
    std::stringstream newName;
    if(m_objectNames[nameBase]) {
        m_objectNames[nameBase] = m_objectNames[nameBase] + 1;
        newName << nameBase << m_objectNames[nameBase];
        return newName.str();
    }
    else {
        m_objectNames[nameBase] = 1;
        newName << nameBase << m_objectNames[nameBase];
        return newName.str();
    }
}
