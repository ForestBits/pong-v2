//allows the user to select a number from a list using up/down arrows

#ifndef NUMBERSELECT_H
#define NUMBERSELECT_H

#include <vector>
#include <functional>
#include <string>
#include "../Resource.h"
#include "IInput.h"

class NumberSelect : public IInput
{
    std::vector<int> numbers;

    int currentIndex;

    sf::RectangleShape box;

    sf::ConvexShape leftArrow;
    sf::ConvexShape rightArrow;

    sf::Text contents;
    sf::Text label;

    std::function<void()> function;

    void recalculate();

public:
    NumberSelect(Resource & resource);

    NumberSelect(Resource & resource, const std::vector<int> & numbers, int initialNumber, sf::Vector2i position, std::string label = "");

    int getSelectedNumber();

    void setSelectedNumber(int number);

    void setPosition(sf::Vector2i position);

    void setText(std::string text);

    void setOnChange(std::function<void()> function);

    void setNumbers(const std::vector<int> & numbers, int initialNumber);

    void update(sf::Vector2i mousePosition, EventQueue events, SoundPlayer & soundPlayer);

    void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

#endif
