#include <cassert>
#include "Slider.h"

Slider::Slider(Resource & resource) : Slider(resource, "", 0, sf::Vector2i(0, 0))
{

}

Slider::Slider(Resource & resource, std::string string, float percent, sf::Vector2i position) : text(string, resource.getFont(), 25), active(false)
{
    assert(percent >= 0 && percent <= 1);

    text.setColor(sf::Color::Black);

    box.setFillColor(sf::Color::Transparent);
    box.setOutlineThickness(1);
    box.setOutlineColor(sf::Color::Black);

    if (string == "")
        box.setSize(sf::Vector2f(100, 20));
    else
        box.setSize(sf::Vector2f(string.length()*20, text.getGlobalBounds().height));


    slider.setSize(sf::Vector2f(5, 30));
    slider.setPosition(box.getPosition().x + (percent*(box.getSize().x - slider.getSize().x)), box.getPosition().y - 5);
    slider.setFillColor(sf::Color::Transparent);
    slider.setOutlineThickness(1);
    slider.setOutlineColor(sf::Color::Black);

    setPosition(position);
}

float Slider::getPercent()
{
    return percent;
}

void Slider::setPercent(float percent)
{
    assert(percent >= 0 && percent <= 1);

    this->percent = percent;

    if (function)
        function(percent);
}

void Slider::setPosition(sf::Vector2i position)
{
    box.setPosition(position.x, position.y);

    slider.setPosition(box.getPosition().x + (percent*(box.getSize().x - slider.getSize().x)), box.getPosition().y - 5);

    sf::Vector2f textPosition(static_cast<float> (box.getPosition().x - (text.getGlobalBounds().width + 10)), static_cast<float> (box.getPosition().y - 3));

    text.setPosition(textPosition);
}

void Slider::setText(std::string string)
{
    text.setString(string);

    if (string.empty())
    {
        box.setSize(sf::Vector2f(100, 20));

        slider.setSize(sf::Vector2f(5, 30));
    }
    else
    {
        box.setSize(sf::Vector2f(100, text.getGlobalBounds().height));

        slider.setSize(sf::Vector2f(5, text.getGlobalBounds().height + 10));
    }

    setPosition(sf::Vector2i(box.getPosition().x, box.getPosition().y));
}

void Slider::setOnMove(std::function<void (float percent)> function)
{
    this->function = function;
}

void Slider::update(sf::Vector2i mousePosition, EventQueue events, SoundPlayer & soundPlayer)
{
    sf::FloatRect rect = slider.getGlobalBounds();

    for (auto evt : events)
    {
        if (evt.type == sf::Event::MouseButtonPressed)
            if (rect.contains(mousePosition.x, mousePosition.y))
                active = true;

        if (active && evt.type == sf::Event::MouseButtonReleased)
        {
            soundPlayer.play(Sounds::CLICK_SOUND);

            active = false;
        }
    }

    if (active)
    {
        //fix it so the mouse is over the middle of the slider

        float startX = slider.getPosition().x;

        sf::Vector2f actualPosition(mousePosition.x - slider.getSize().x/2, slider.getPosition().y);    
        
        if (actualPosition.x < box.getPosition().x)
            actualPosition.x = box.getPosition().x;
        else if (mousePosition.x > box.getPosition().x + box.getSize().x)
            actualPosition.x = box.getPosition().x + box.getSize().x;

        percent = (actualPosition.x - box.getPosition().x)/box.getSize().x;

        slider.setPosition(box.getPosition().x + (percent*(box.getSize().x - slider.getSize().x)), slider.getPosition().y);

        if (slider.getPosition().x != startX)
        {
            if (function)
                function(percent);
        }
    }
}

void Slider::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(box);
    target.draw(slider);
    target.draw(text);
}