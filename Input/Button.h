//a simple text button - allows action when it is clicked

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <string>
#include <functional>
#include "Input.h"

namespace pong { namespace input {

class Button : public Input
{
    sf::Text text;

    sf::Sound & clickSound;

    sf::Vector2i position;

    bool centered;

    std::function<void ()> onClick;

    void recalculate();

public:
    Button(const sf::Font & font, sf::Sound & clickSound);

    void setText(const std::string & string);
    void setPosition(const sf::Vector2i & position, bool centered = true);
    void setOnClick(std::function<void ()> function);

    void update(EventQueue events, const sf::Vector2i & mousePosition);
    
    void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

}}

#endif
