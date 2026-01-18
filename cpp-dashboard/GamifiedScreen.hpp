// GamifiedScreen.hpp
// Placeholder for Gamified View

#ifndef GAMIFIED_SCREEN_HPP
#define GAMIFIED_SCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>

class GamifiedScreen : public Screen {
private:
    sf::Font* font;
    sf::Text title;
    sf::Text placeholder;
    Button backButton;
    std::function<void(ScreenType)> onNavigate;

public:
    GamifiedScreen(sf::Font& screenFont, std::function<void(ScreenType)> navigateCallback)
        : font(&screenFont), onNavigate(navigateCallback),
          backButton(20.f, 20.f, 100.f, 40.f, "Back", *font) {
        
        title.setFont(*font);
        title.setString("Gamified View");
        title.setCharacterSize(32);
        title.setFillColor(sf::Color(50, 50, 50));
        title.setPosition(200.f, 30.f);

        placeholder.setFont(*font);
        placeholder.setString("Gamification Features\n\n[Placeholder Screen]\n\nXP, Levels, Achievements, Streaks,\nand Rewards will be displayed here.");
        placeholder.setCharacterSize(20);
        placeholder.setFillColor(sf::Color(100, 100, 100));
        placeholder.setPosition(150.f, 200.f);

        backButton.setOnClick([this]() {
            if (onNavigate) onNavigate(ScreenType::MENU);
        });
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {
        backButton.handleEvent(event, window);
    }

    void update(float deltaTime) override {
        backButton.update();
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(title);
        backButton.draw(window);
        window.draw(placeholder);
    }

    ScreenType getType() const override {
        return ScreenType::GAMIFIED;
    }
};

#endif
