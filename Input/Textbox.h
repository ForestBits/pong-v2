//a singleline text input

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include "../Resource.h"
#include "Input.h"



class Textbox : public IInput
{
    bool activated;

    char lastEntered;

    int maxCharacters;

    std::string contentsString;

    sf::Text label;
    sf::Text contents;

    sf::RectangleShape box;
    sf::RectangleShape cursor;

    sf::Clock keyDelay;
    sf::Clock blinkDelay;

    std::function<void()> function;

public:
    Textbox(Resource & resource, int maxCharacters = 20, sf::Vector2i position = sf::Vector2i(0, 0), std::string labelString = "", std::string contentsString = "");

    std::string getContents();

    void setPosition(sf::Vector2i position);

    void setLabel(std::string label);

    void setContents(std::string contents);

    void setOnContentsChange(std::function<void()> function);

    void update(sf::Vector2i mousePosition, EventQueue events, SoundPlayer & soundPlayer);

    void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};


#endif
