// ScreenManager.hpp
// Manages screen navigation and transitions

#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include "Screen.hpp"
#include <memory>
#include <map>

class ScreenManager {
private:
    std::map<ScreenType, std::unique_ptr<Screen>> screens;
    Screen* currentScreen;

public:
    ScreenManager() : currentScreen(nullptr) {}

    void addScreen(ScreenType type, std::unique_ptr<Screen> screen) {
        screens[type] = std::move(screen);
    }

    void setScreen(ScreenType type) {
        auto it = screens.find(type);
        if (it != screens.end()) {
            currentScreen = it->second.get();
        }
    }

    Screen* getCurrentScreen() {
        return currentScreen;
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
        if (currentScreen) {
            currentScreen->handleEvent(event, window);
        }
    }

    void update(float deltaTime) {
        if (currentScreen) {
            currentScreen->update(deltaTime);
        }
    }

    void draw(sf::RenderWindow& window) {
        if (currentScreen) {
            currentScreen->draw(window);
        }
    }
};

#endif
