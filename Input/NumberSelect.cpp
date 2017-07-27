#include <cassert>
#include "../Utility/StringNumberConvert.h"
#include "NumberSelect.h"

NumberSelect::NumberSelect(Resource & resource) : NumberSelect(resource, {0}, 0, sf::Vector2i(0, 0))
{

}

NumberSelect::NumberSelect(Resource & resource, const std::vector<int> & numbers, int initialNumber, sf::Vector2i position, std::string label)
{
    this->label.setFont(resource.getFont());
    contents.setFont(resource.getFont());

    box.setSize(sf::Vector2f(100, 30));
    box.setFillColor(sf::Color::Transparent);
    box.setOutlineThickness(1);
    box.setOutlineColor(sf::Color::Black);

    leftArrow.setPointCount(3);
    leftArrow.setPoint(0, sf::Vector2f(0, 0));
    leftArrow.setPoint(1, sf::Vector2f(10, 10));
    leftArrow.setPoint(2, sf::Vector2f(20, 0));
    leftArrow.setFillColor(sf::Color::Black);
    leftArrow.setOrigin(leftArrow.getLocalBounds().width/2, leftArrow.getLocalBounds().height/2);
    
    rightArrow.setPointCount(3);
    rightArrow.setPoint(0, sf::Vector2f(0, 0));
    rightArrow.setPoint(1, sf::Vector2f(10, 10));
    rightArrow.setPoint(2, sf::Vector2f(20, 0));
    rightArrow.setFillColor(sf::Color::Black);
    rightArrow.setOrigin(rightArrow.getLocalBounds().width/2, rightArrow.getLocalBounds().height/2);
    rightArrow.setRotation(180);

    contents.setColor(sf::Color::Black);

    this->label.setColor(sf::Color::Black);

    setNumbers(numbers, initialNumber);

    contents.setString(toString<int>(initialNumber));

    setPosition(position);

    setText(label);
}

//sets all positions correctly
void NumberSelect::recalculate()
{
    leftArrow.setPosition(box.getPosition().x + leftArrow.getLocalBounds().width, box.getPosition().y + leftArrow.getLocalBounds().height + 5);

    contents.setPosition((box.getPosition().x + box.getSize().x/2), box.getPosition().y + contents.getLocalBounds().height/2);

    rightArrow.setPosition((box.getGlobalBounds().left + box.getSize().x) - rightArrow.getLocalBounds().width, box.getPosition().y + rightArrow.getLocalBounds().height + 5);

    label.setPosition((box.getPosition().x - 3) - label.getLocalBounds().width, box.getPosition().y);
}

int NumberSelect::getSelectedNumber()
{
    return numbers[currentIndex];
}

void NumberSelect::setText(std::string text)
{
    label.setString(text);

    recalculate();
}

void NumberSelect::setNumbers(const std::vector<int> & numbers, int initialNumber)
{
    //if an arrow was white before, it will not "come back" without this
    leftArrow.setFillColor(sf::Color::Black);
    rightArrow.setFillColor(sf::Color::Black);

    bool contains = false;
    
    for (int number : numbers)
        if (number == initialNumber)
        {
            contains = true;

            break;
        }

    assert(contains);

    this->numbers = numbers;

    this->currentIndex = numbers[std::find(numbers.begin(), numbers.end(), initialNumber) - numbers.begin()];
    
    contents.setString(toString(numbers[currentIndex]));

    contents.setOrigin(contents.getLocalBounds().width/2, contents.getLocalBounds().height/2);

    recalculate();

    if (currentIndex == numbers.size() - 1)
        rightArrow.setFillColor(sf::Color::White);

    if (currentIndex == 1)
        leftArrow.setFillColor(sf::Color::Black);

    if (currentIndex == 0)
        leftArrow.setFillColor(sf::Color::White);

    if (currentIndex == numbers.size() - 2)
        rightArrow.setFillColor(sf::Color::Black);
}

void NumberSelect::setOnChange(std::function<void()> function)
{
    this->function = function;
}

void NumberSelect::setPosition(sf::Vector2i position)
{
    box.setPosition(position.x, position.y);

    recalculate();
}


void NumberSelect::update(sf::Vector2i mousePosition, EventQueue events, SoundPlayer & soundPlayer)
{
    for (auto evt : events)
        if (evt.type == sf::Event::MouseButtonReleased)
        {
            if (leftArrow.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
            {
                if (currentIndex > 0)
                {
                    --currentIndex;

                    contents.setString(toString(numbers[currentIndex]));

                    contents.setOrigin(contents.getLocalBounds().width/2, contents.getLocalBounds().height/2);

                    if (currentIndex == 0)
                        leftArrow.setFillColor(sf::Color::White);

                    if (currentIndex == numbers.size() - 2)
                        rightArrow.setFillColor(sf::Color::Black);

                    soundPlayer.play(Sounds::CLICK_SOUND);

                    if (function)
                        function();
                }
            }

            if (rightArrow.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
            {
                if (currentIndex + 1 < numbers.size())
                {
                    ++currentIndex;

                    contents.setString(toString(numbers[currentIndex]));

                    contents.setOrigin(contents.getLocalBounds().width/2, contents.getLocalBounds().height/2);

                    if (currentIndex == numbers.size() - 1)
                        rightArrow.setFillColor(sf::Color::White);

                    if (currentIndex == 1)
                        leftArrow.setFillColor(sf::Color::Black);

                    if (function)
                        function();
                }
            }
        }
}

void NumberSelect::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(box);
    target.draw(label);
    target.draw(contents);
    target.draw(leftArrow);
    target.draw(rightArrow);
}