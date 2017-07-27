//a slider bar

#ifndef SLIDER_H
#define SLIDER_H

#include <string>
#include <functional>
#include "../Resource.h"
#include "IInput.h"



class Slider : public IInput
{
    bool active; 

    //[0, 1]
    float percent;

    //to the left of the box, indicating what it represents
    sf::Text text;

    sf::RectangleShape box;
    sf::RectangleShape slider;

    std::function<void (float percent)> function;
public:
    Slider(Resource & resource);
    Slider(Resource & resource, std::string string, float percent, sf::Vector2i position);

    float getPercent();

    //[0, 1]
    void setPercent(float percent);

    void setPosition(sf::Vector2i position);
    
    void setText(std::string text);

    void setOnMove(std::function<void (float percent)> function);

    void update(sf::Vector2i mousePosition, EventQueue events, SoundPlayer & soundPlayer);

    void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

#endif
