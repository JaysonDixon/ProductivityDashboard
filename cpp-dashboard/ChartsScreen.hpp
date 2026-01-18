// ChartsScreen.hpp
// Placeholder for Charts View

#ifndef CHARTS_SCREEN_HPP
#define CHARTS_SCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>

class ChartsScreen : public Screen {
private:
    sf::Font* font;
    sf::Text title;
    sf::Text placeholder;
    Button backButton;
    std::function<void(ScreenType)> onNavigate;

public:
    ChartsScreen(sf::Font& screenFont, std::function<void(ScreenType)> navigateCallback)
        : font(&screenFont), onNavigate(navigateCallback),
          backButton(20.f, 20.f, 100.f, 40.f, "Back", *font) {
        
        title.setFont(*font);
        title.setString("Charts View");
        title.setCharacterSize(32);
        title.setFillColor(sf::Color(50, 50, 50));
        title.setPosition(200.f, 30.f);

        placeholder.setFont(*font);
        placeholder.setString("Charts and Analytics\n\n[Placeholder Screen]\n\nBar charts, line graphs, and trend visualizations\nwill be displayed here.");
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
        return ScreenType::CHARTS;
    }
};

#endif
