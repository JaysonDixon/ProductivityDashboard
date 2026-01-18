// Button.hpp
// UI Button Component for SFML

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font* font;
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color pressedColor;
    bool isHovered;
    bool isPressed;
    std::function<void()> onClick;

public:
    Button(float x, float y, float width, float height, 
           const std::string& buttonText, sf::Font& buttonFont,
           sf::Color normal = sf::Color(100, 100, 200),
           sf::Color hover = sf::Color(120, 120, 220),
           sf::Color pressed = sf::Color(80, 80, 180))
        : font(&buttonFont), normalColor(normal), hoverColor(hover), 
          pressedColor(pressed), isHovered(false), isPressed(false) {
        
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(normalColor);
        shape.setOutlineThickness(2.f);
        shape.setOutlineColor(sf::Color(50, 50, 50));

        text.setFont(*font);
        text.setString(buttonText);
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::White);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                       textBounds.top + textBounds.height / 2.0f);
        text.setPosition(x + width / 2.0f, y + height / 2.0f);
    }

    void setOnClick(std::function<void()> callback) {
        onClick = callback;
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        isHovered = shape.getGlobalBounds().contains(mousePosF);

        if (event.type == sf::Event::MouseButtonPressed && 
            event.mouseButton.button == sf::Mouse::Left && isHovered) {
            isPressed = true;
        }

        if (event.type == sf::Event::MouseButtonReleased && 
            event.mouseButton.button == sf::Mouse::Left) {
            if (isPressed && isHovered && onClick) {
                onClick();
            }
            isPressed = false;
        }
    }

    void update() {
        if (isPressed) {
            shape.setFillColor(pressedColor);
        } else if (isHovered) {
            shape.setFillColor(hoverColor);
        } else {
            shape.setFillColor(normalColor);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

    void setPosition(float x, float y) {
        shape.setPosition(x, y);
        sf::Vector2f size = shape.getSize();
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                       textBounds.top + textBounds.height / 2.0f);
        text.setPosition(x + size.x / 2.0f, y + size.y / 2.0f);
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }
};

#endif
