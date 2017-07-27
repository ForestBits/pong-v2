#include "Textbox.h"

Textbox::Textbox(Resource & resource, int maxCharacters, sf::Vector2i position, std::string labelString, std::string contentsString) : activated(false), maxCharacters(maxCharacters), lastEntered('\0')
{
    label.setFont(resource.getFont());
    label.setCharacterSize(25);
    label.setColor(sf::Color::Black);
    label.setString(labelString);

    contents.setFont(resource.getFont());
    contents.setCharacterSize(25);
    contents.setColor(sf::Color::Black);
    contents.setString(contentsString);

    box.setFillColor(sf::Color::Transparent);
    box.setOutlineThickness(1);
    box.setOutlineColor(sf::Color::Black);
    box.setSize(sf::Vector2f(maxCharacters*20, 33));

    setPosition(position);

    cursor.setFillColor(sf::Color::Black);
    cursor.setSize(sf::Vector2f(2, 30));
    cursor.setPosition(box.getPosition().x + 4, box.getPosition().y + 2);

    
}

std::string Textbox::getContents()
{
    return contentsString;
}

void Textbox::setContents(std::string string)
{
    contents.setString(string);
}

void Textbox::setLabel(std::string string)
{
    label.setString(string);

    setPosition(sf::Vector2i(box.getPosition().x, box.getPosition().y));
}

void Textbox::setPosition(sf::Vector2i position)
{
    box.setPosition(position.x, position.y);

    sf::Vector2f textPosition(static_cast<float> (box.getPosition().x - (label.getGlobalBounds().width + 10)), static_cast<float> (box.getPosition().y + 1));

    label.setPosition(textPosition);

    contents.setPosition(box.getPosition().x + 2, box.getPosition().y + 2);

    cursor.setPosition(contents.getPosition().x + contents.getGlobalBounds().width + 2, box.getPosition().y + 2);
}

void Textbox::setOnContentsChange(std::function<void()> function)
{
    this->function = function;
}

void Textbox::update(sf::Vector2i mousePosition, EventQueue events, SoundPlayer & soundPlayer)
{
    if (blinkDelay.getElapsedTime().asSeconds() < 0.75)
        cursor.setFillColor(sf::Color::Black);
    else
        cursor.setFillColor(sf::Color::Transparent);

    if (blinkDelay.getElapsedTime().asSeconds() >= 1.5)
        blinkDelay.restart();

    for (sf::Event evt : events)
    {
        if (evt.type == sf::Event::MouseButtonPressed)
        {
            int textLength = maxCharacters*10;

            if (box.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
            {
                activated = !activated;

                if (activated)
                    blinkDelay.restart();
            }
        }
        
        if (evt.type == sf::Event::TextEntered && activated)
        {
            //ASCII char
            if (evt.text.unicode < 128)
            {
                char pressed = static_cast<char> (evt.text.unicode);

                //enter
                if (pressed == '\n' || pressed == '\r')
                    continue;

                if (!(contents.getString().getSize() < maxCharacters || pressed == '\b'))
                    continue;

                if (pressed == '\b' && contents.getString().isEmpty())
                    continue;

                if (lastEntered == pressed)
                {
                    if (keyDelay.getElapsedTime().asSeconds() > 0.2)
                    {
                        keyDelay.restart();

                        if (pressed == '\b')
                            contentsString.pop_back();
                        else
                            contentsString.push_back(pressed);
                    }
                }
                else
                {
                    if (pressed == '\b')
                        contentsString.pop_back();
                    else
                        contentsString.push_back(pressed);

                    keyDelay.restart();
                }
                
                bool changed = false;

                if (contentsString.length() != contents.getString().getSize())
                    changed = true;

                contents.setString(contentsString);

                if (changed)
                    cursor.setPosition(contents.getPosition().x + contents.getGlobalBounds().width + 2, box.getPosition().y + 2);

                soundPlayer.play(Sounds::CLICK_SOUND);

                if (function)
                    function();

                lastEntered = pressed;
            }
        }
    }
}

void Textbox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(box);
    target.draw(label);
    target.draw(contents);
    
    if (activated)
        target.draw(cursor);
}
