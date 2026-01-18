// MenuScreen.hpp
// T1 - Main Menu Interface with Navigation

#ifndef MENU_SCREEN_HPP
#define MENU_SCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include <vector>
#include <functional>

class MenuScreen : public Screen {
private:
    sf::Font* font;
    sf::Text title;
    std::vector<Button> menuButtons;
    std::function<void(ScreenType)> onNavigate;
    float windowWidth;
    float windowHeight;

public:
    MenuScreen(sf::Font& menuFont, float winWidth, float winHeight, 
               std::function<void(ScreenType)> navigateCallback)
        : font(&menuFont), onNavigate(navigateCallback), 
          windowWidth(winWidth), windowHeight(winHeight) {
        
        title.setFont(*font);
        title.setString("Productivity Dashboard");
        title.setCharacterSize(42);
        title.setFillColor(sf::Color(50, 50, 50));
        title.setStyle(sf::Text::Bold);
        
        sf::FloatRect titleBounds = title.getLocalBounds();
        title.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
                        titleBounds.top + titleBounds.height / 2.0f);
        title.setPosition(windowWidth / 2.0f, 80.f);

        createButtons();
    }

    void createButtons() {
        float buttonWidth = 300.f;
        float buttonHeight = 60.f;
        float startY = 200.f;
        float spacing = 80.f;
        float centerX = (windowWidth - buttonWidth) / 2.0f;

        Button dashboardBtn(centerX, startY, buttonWidth, buttonHeight, 
                           "Dashboard", *font,
                           sf::Color(70, 130, 180),
                           sf::Color(100, 160, 210),
                           sf::Color(50, 110, 160));
        dashboardBtn.setOnClick([this]() { 
            if (onNavigate) onNavigate(ScreenType::DASHBOARD); 
        });
        menuButtons.push_back(dashboardBtn);

        Button chartsBtn(centerX, startY + spacing, buttonWidth, buttonHeight, 
                        "Charts", *font,
                        sf::Color(60, 179, 113),
                        sf::Color(90, 209, 143),
                        sf::Color(40, 159, 93));
        chartsBtn.setOnClick([this]() { 
            if (onNavigate) onNavigate(ScreenType::CHARTS); 
        });
        menuButtons.push_back(chartsBtn);

        Button gamifiedBtn(centerX, startY + spacing * 2, buttonWidth, buttonHeight, 
                          "Gamified View", *font,
                          sf::Color(255, 140, 0),
                          sf::Color(255, 170, 50),
                          sf::Color(225, 120, 0));
        gamifiedBtn.setOnClick([this]() { 
            if (onNavigate) onNavigate(ScreenType::GAMIFIED); 
        });
        menuButtons.push_back(gamifiedBtn);

        Button settingsBtn(centerX, startY + spacing * 3, buttonWidth, buttonHeight, 
                          "Settings", *font,
                          sf::Color(147, 112, 219),
                          sf::Color(177, 142, 249),
                          sf::Color(127, 92, 199));
        settingsBtn.setOnClick([this]() { 
            if (onNavigate) onNavigate(ScreenType::SETTINGS); 
        });
        menuButtons.push_back(settingsBtn);
    }

    void handleResize(float newWidth, float newHeight) {
        windowWidth = newWidth;
        windowHeight = newHeight;

        sf::FloatRect titleBounds = title.getLocalBounds();
        title.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
                        titleBounds.top + titleBounds.height / 2.0f);
        title.setPosition(windowWidth / 2.0f, 80.f);

        float buttonWidth = 300.f;
        float buttonHeight = 60.f;
        float startY = 200.f;
        float spacing = 80.f;
        float centerX = (windowWidth - buttonWidth) / 2.0f;

        for (size_t i = 0; i < menuButtons.size(); i++) {
            menuButtons[i].setPosition(centerX, startY + spacing * i);
        }
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {
        for (auto& button : menuButtons) {
            button.handleEvent(event, window);
        }

        if (event.type == sf::Event::Resized) {
            handleResize(static_cast<float>(event.size.width), 
                        static_cast<float>(event.size.height));
        }
    }

    void update(float deltaTime) override {
        for (auto& button : menuButtons) {
            button.update();
        }
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(title);
        for (auto& button : menuButtons) {
            button.draw(window);
        }
    }

    ScreenType getType() const override {
        return ScreenType::MENU;
    }
};

#endif
