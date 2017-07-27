//ye olde' checkbox

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <string>
#include <functional>
#include "../Resource.h"
#include "IInput.h"

class Checkbox : public IInput
{
    bool checked;

    //label
    sf::Text text;

    std::function<void (bool checked)> function;

    sf::RectangleShape box;

public:
    Checkbox(Resource & resource);
    Checkbox(Resource & resource, std::string string, sf::Vector2i position, bool checked);

    bool isChecked();

    void setChecked(bool checked);

    void setPosition(sf::Vector2i position);

    void setText(std::string string);

    void setOnToggle(std::function<void (bool checked)> function);

    void update(sf::Vector2i mousePosition, EventQueue events, SoundPlayer & soundPlayer);

    void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

#endif
