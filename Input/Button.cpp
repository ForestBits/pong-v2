#include "Button.h"

using namespace pong;
using namespace pong::input;

Button::Button(const sf::Font & font, sf::Sound & clickSound) : clickSound(clickSound)
{
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
}

void Button::recalculate()
{
    if (centered)
        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
    else
        text.setOrigin(0, 0);

    text.setPosition(position.x, position.y);
}

void Button::setText(const std::string & string)
{
    text.setString(string);

    recalculate();
}

void Button::setPosition(const sf::Vector2i & position, bool centered)
{
    this->position = position;
    this->centered = centered;

    if (centered)
        text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    else //it may have been set centered before, so clear the origin
        text.setOrigin(0, 0);

    text.setPosition(position.x, position.y);
}

void Button::setOnClick(std::function<void ()> function) {onClick = std::move(function);}

void Button::update(EventQueue events, const sf::Vector2i & mousePosition)
{
    bool mouseOver = text.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y));

    if (mouseOver && text.getScale().x < 1.5)
        text.scale(1.02, 1);

    if (!mouseOver && text.getScale().x > 1)
        text.scale(0.98, 1);


    for (auto event : events)
    {
        if (event.type == sf::Event::MouseButtonPressed)
            if (mouseOver)
            {
                clickSound.play();

                if (onClick)
                    onClick();
            }
    }
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const {target.draw(text);}