
// Copyright 2018 Corey Selover

#include "Manager.h"

Manager::Manager() {}

void Manager::update() {
    std::map<std::string, ManagedObject*>::iterator itr;
    for(itr = m_managed.begin(); itr != m_managed.end(); itr++) {
        itr->second->update();
    }
}

void Manager::draw() {
    std::map<std::string, ManagedObject*>::iterator itr;
    for(itr = m_managed.begin(); itr != m_managed.end(); itr++) {
        itr->second->draw();
    }
}

Manager::~Manager() {
    std::map<std::string, ManagedObject*>::iterator itr;
    for(itr = m_managed.begin(); itr != m_managed.end(); itr++) {
        delete itr->second;
    }
    m_managed.clear();
}
