#include <cassert>
#include "Checkbox.h"

Checkbox::Checkbox(Resource & resource) : Checkbox(resource, "", sf::Vector2i(0, 0), false)
{
    
}

Checkbox::Checkbox(Resource & resource, std::string string, sf::Vector2i position, bool checked) : text(string, resource.getFont(), 25), checked(checked)
{
    text.setColor(sf::Color::Black);

    box.setFillColor(sf::Color::Transparent);
    box.setOutlineThickness(1);
    box.setOutlineColor(sf::Color::Black);

    if (string == "")
        box.setSize(sf::Vector2f(20, 20));
    else
        box.setSize(sf::Vector2f(text.getGlobalBounds().height, text.getGlobalBounds().height));

    setPosition(position);
}

bool Checkbox::isChecked() 
{
    return checked;
}

void Checkbox::setChecked(bool checked)
{
    this->checked = checked;
}

void Checkbox::setText(std::string string)
{
    text.setString(string);

    box.setSize(sf::Vector2f(text.getGlobalBounds().height, box.getGlobalBounds().height));

    //makes it recalculate offset
    setPosition(sf::Vector2i(box.getPosition().x, box.getPosition().y));
}

void Checkbox::setPosition(sf::Vector2i position)
{
    box.setPosition(position.x, position.y);

    sf::Vector2f textPosition(static_cast<float> (position.x - (text.getGlobalBounds().width + 10)), static_cast<float> (position.y - 3));

    text.setPosition(textPosition);
}

void Checkbox::setOnToggle(std::function<void (bool checked)> function)
{
    this->function = function;
}

void Checkbox::update(sf::Vector2i mousePosition, EventQueue events, SoundPlayer & soundPlayer)
{
    sf::FloatRect rect = box.getGlobalBounds();

    bool mouseOver = rect.contains(sf::Vector2f(mousePosition.x, mousePosition.y));

    for (sf::Event evt : events)
        if (evt.type == sf::Event::MouseButtonReleased)
            if (mouseOver)
            {
                checked = !checked;

                soundPlayer.play(Sounds::CLICK_SOUND);

                if (function)
                    function(checked);
            }
}

void Checkbox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(box);
    target.draw(text);

    if (checked)
    {
        static sf::RectangleShape down(sf::Vector2f(7, 3));

        down.setPosition(box.getPosition().x + 5, box.getPosition().y + 10);
        down.setRotation(50);
        down.setFillColor(sf::Color::Black);

        static sf::RectangleShape up(sf::Vector2f(14, 3));

        up.setPosition(box.getPosition().x + 6, box.getPosition().y + 15);
        up.setRotation(-60);
        up.setFillColor(sf::Color::Black);



        target.draw(down);
        target.draw(up);
    }
}

