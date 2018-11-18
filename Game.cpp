
// Copyright 2018 Corey Selover

#include "Game.h"

// External libs
#include <fstream>

// Project files
#include "Console.h"
#include "Manager.h"
#include "Entity.h"
#include "Splash.h"
#include "Map.h"
#include "Texture.h"
#include "HudObject.h"

Game::Game() {}

BootError Game::boot() {

    // Set random seed.
    std::srand(std::time(nullptr));

    loadGameValues();

    // Window
    m_window.create(sf::VideoMode::getFullscreenModes()[0], "Genesis", sf::Style::Fullscreen);
    //m_window.create(sf::VideoMode(800,600), "Genesis");
    m_window.setVerticalSyncEnabled(true);

    // Set up managers
    m_managers[TEXTURE_MANAGER] = new Manager();
    m_managers[SCREEN_MANAGER] = new Manager();
    m_managers[HUD_MANAGER] = new Manager();

    // Console
    m_console = new Console(this);

    // TODO - turn these back on for release.
    //m_managers[SCREEN_MANAGER]->add("happy_rock", new Splash(this, "resources/textures/splash.png", sf::seconds(3.0f)));
    //m_managers[SCREEN_MANAGER]->add("disclaimer", new Splash(this, "resources/textures/splash2.png", sf::seconds(3.0f)));
    m_managers[SCREEN_MANAGER]->add("map", new Map(this));

    //m_screenQueue.push("happy_rock");
    //m_screenQueue.push("disclaimer");
    m_screenQueue.push("map");
    m_currentScreen = m_screenQueue.front();

    // HUD
    // TODO - Does this belong here?
    m_managers[HUD_MANAGER]->add("mana_hud", new ManaHudObject(this,
                                                           "resources/textures/TEXTURE_MANA.png",
                                                           sf::IntRect(0, 0, 300, 50), 30, 60, 3, true));
    m_managers[HUD_MANAGER]->add("grass_aura_hud", new AuraHudObject(this,
                                                           "resources/textures/TEXTURE_AURA_GRASS.png",
                                                           sf::IntRect(0, 0, 64, 64), 360, 70, 3, true));
    m_managers[HUD_MANAGER]->add("rock_aura_hud", new AuraHudObject(this,
                                                           "resources/textures/TEXTURE_AURA_ROCK.png",
                                                           sf::IntRect(0, 0, 64, 64), 440, 70, 3, true));
    m_managers[HUD_MANAGER]->add("water_aura_hud", new AuraHudObject(this,
                                                           "resources/textures/TEXTURE_AURA_WATER.png",
                                                           sf::IntRect(0, 0, 64, 64), 520, 70, 3, true));

    m_running = true;

    return BOOT_SUCCESS;
}

RunError Game::run() {

    float clockRemainder = 0;

    while(m_running) {

        /* We do this now to ensure that events (particularly mouse clicks)
         * are relative to the "world" and not, say the HUD.
         */
        m_window.setView(static_cast<Screen*>(m_managers[SCREEN_MANAGER]->get(m_currentScreen))->getView());

        sf::Event event;
        while (m_window.pollEvent(event)) {
            processInput(event);
        }

        // No more screens to display.  Time to quit.
        if(m_screenQueue.empty()) {
            shutdown();
        }
        if(!m_running) return RUN_SUCCESS;

        if(m_gameClock.getElapsedTime().asSeconds() > 1/60.f - clockRemainder) {

            // Update managers as appropriate.
            m_currentScreen = m_screenQueue.front();
            m_managers[SCREEN_MANAGER]->get(m_currentScreen)->update();
            if (m_currentScreen.compare("map") == 0) m_managers[HUD_MANAGER]->update();
            m_console->update();

            clockRemainder = m_gameClock.restart().asSeconds() - 1/60.f;

            // Draw game objects, screens, etc.
            m_window.clear();
            m_managers[SCREEN_MANAGER]->get(m_currentScreen)->draw();

            // Draw console
            // TODO - this line should be unnecessary if HUD_MANAGER is the last to draw.
            // Might be good to keep it in place in case manager updating gets shuffled.
            m_window.setView(m_window.getDefaultView());
            m_managers[HUD_MANAGER]->draw();
            m_console->draw();

            // Display
            m_window.display();
        }
    }

    return RUN_SUCCESS;
}

void Game::processInput(sf::Event event) {
    if (event.type == sf::Event::Closed) {
        shutdown();
    }
    // Keyboard
    if (event.type == sf::Event::TextEntered && m_console->active()) {
        m_console->handle(event);
    }
    else if (event.type == sf::Event::KeyPressed) {
        // Meta keys
        if(event.key.code == sf::Keyboard::Tilde) {
            m_console->toggle();
        }
        // Player control or GUI interaction
        else if(!m_console->active()) {
            static_cast<Screen*>(m_managers[SCREEN_MANAGER]->get(m_currentScreen))->processInput(event);
        }
    }
    else if (event.type == sf::Event::KeyReleased) {
        // Player control or GUI interaction
        if(!m_console->active()) {
            static_cast<Screen*>(m_managers[SCREEN_MANAGER]->get(m_currentScreen))->processInput(event);
        }
    }
    // Mouse
    else if (event.type == sf::Event::MouseButtonPressed) {
        static_cast<Screen*>(m_managers[SCREEN_MANAGER]->get(m_currentScreen))->processInput(event);
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        static_cast<Screen*>(m_managers[SCREEN_MANAGER]->get(m_currentScreen))->processInput(event);
    }
}

ShutdownError Game::shutdown() {

    m_running = false;

    delete m_console;

    // Shutdown managers
    std::map<ManagerType, Manager*>::iterator itr;
    for(itr = m_managers.begin(); itr != m_managers.end(); itr++) {
        itr->second->shutdown();
    }

    // Delete managers
    for(itr = m_managers.begin(); itr != m_managers.end(); itr++) {
        delete itr->second;
    }
    m_managers.clear();

    m_window.close();

    return SHUTDOWN_SUCCESS;
}

///////////////////////////////////
//      Drawing and Screen       //
///////////////////////////////////

void Game::draw(sf::Drawable& drawable) {
    m_window.draw(drawable);
}

void Game::nextScreen() {
    if(!m_screenQueue.empty()) {
        m_screenQueue.pop();
    }
    if(!m_screenQueue.empty()) {
        static_cast<Screen*>(m_managers[SCREEN_MANAGER]->get(m_screenQueue.front()))->restartClock();
    }
}

///////////////////////////////////
//      Getters and Setters      //
///////////////////////////////////

Entity* Game::entity(std::string name) {
    // TODO - this should throw an error if the entity doesn't exist
    return static_cast<Screen*>(m_managers[SCREEN_MANAGER]->get(m_currentScreen))->entity(name);
}

Texture* Game::texture(std::string name) {
    return static_cast<Texture*>(m_managers[TEXTURE_MANAGER]->get(name));
}

Texture* Game::addTexture(std::string filePath, bool repeated) {
    return static_cast<Texture*>(m_managers[TEXTURE_MANAGER]->add(filePath, new Texture(this, filePath, repeated)));
}

Screen* Game::screen(std::string name) {
    return static_cast<Screen*>(m_managers[SCREEN_MANAGER]->get(name));
}

HudObject* Game::hudObject(std::string name) {
    return static_cast<HudObject*>(m_managers[HUD_MANAGER]->get(name));
}

void Game::setView(sf::View view) { m_window.setView(view); }

sf::Vector2f Game::windowCenter() { return sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2); }

sf::Vector2u Game::windowSize() { return m_window.getSize(); }

const sf::View& Game::defaultView() { return m_window.getDefaultView(); }

sf::Vector2i Game::mapCenterAsPixels() { return sf::Vector2i(mapWidth() * tileWidth() / 2, mapHeight() * tileHeight() / 2); }

sf::Vector2i Game::mapCenterAsCoordinates() { return sf::Vector2i(mapWidth() / 2, mapHeight() / 2); }

sf::Vector2f Game::worldCoords(int x, int y) { return m_window.mapPixelToCoords(sf::Vector2i(x,y)); }

int Game::mapWidth() { return std::atoi(m_gameValues["map_width"].c_str()); }

int Game::mapHeight() { return std::atoi(m_gameValues["map_height"].c_str()); }

int Game::tileWidth() { return std::atoi(m_gameValues["tile_width"].c_str()); }

int Game::tileHeight() { return std::atoi(m_gameValues["tile_height"].c_str()); }

///////////////////////////////////
//              Console          //
///////////////////////////////////

void Game::runCommand(std::string command) {
    std::vector<std::string>::iterator itr;
    for(itr = m_commands.begin(); itr != m_commands.end(); itr++) {
        if((*itr) == command) {
            // Do stuff accordingly
            m_console->clean();
            m_console->toggle();
        }
    }
    m_console->displayError("Command not found or syntax invalid:", command);
}

void Game::assignGameValue(std::string variable, std::string value, bool saveToDisk) {
    if(m_gameValues.count(variable)) {
        m_gameValues[variable] = value;
        if(saveToDisk) {
            saveGameValues();
        }
        m_console->clean();
        m_console->toggle();
    }
    else {
        m_console->displayError("Variable unknown or value not valid:", value);
    }
}

std::string Game::getGameValue(std::string variable) {
    if(m_gameValues.count(variable)) {
        return m_gameValues[variable];
    }
    else {
        m_console->displayError("Variable unknown:", variable);
        return "ERROR";
    }
}

void Game::loadGameValues() {
    std::ifstream input( "data.ini" );
    for( std::string line; getline( input, line ); )
    {
        std::string first = line.substr(0, line.find("="));
        std::string second = line.substr(line.find("=") + 1);

        /* The above code will set first and second to the same value if
         * the line contains no = sign.  In other words, if the line is
         * something like [Map], we don't want to parse it and we can
         * ignore it.
         */
        if(first.compare(second) != 0) {
            m_gameValues[first] = second;
        }
    }
}

void Game::saveGameValues() {
    std::cout << "Saving values" << std::endl;
    std::ofstream output;
    output.open("data.ini");
    std::map<std::string, std::string>::iterator itr;
    for (itr = m_gameValues.begin(); itr != m_gameValues.end(); itr++) {
        std::cout << "Writing: " << itr->first << "=" << itr->second << std::endl;
        output<< itr->first << "=" << itr->second << std::endl;
    }
    output.close();
}

///////////////////////////////////
//              Util             //
///////////////////////////////////

void Game::printGameValues() {
    std::map<std::string, std::string>::iterator itr;
    for (itr = m_gameValues.begin(); itr != m_gameValues.end(); itr++) {
        std::cout << itr->first << "=" << itr->second << std::endl;
    }
}




