// Screen.hpp
// Base Screen Interface

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>

enum class ScreenType {
    MENU,
    DASHBOARD,
    CHARTS,
    GAMIFIED,
    SETTINGS
};

class Screen {
public:
    virtual ~Screen() = default;
    virtual void handleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ScreenType getType() const = 0;
};

#endif
