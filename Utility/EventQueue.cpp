#include <SFML/Window.hpp>
#include <cassert>
#include "EventQueue.h"

using namespace pong;

EventQueue::EventQueue(sf::Window & window)
{
    sf::Event event;

    while (window.pollEvent(event))
        events.push_back(event);
}

int EventQueue::getCount() {return events.size();}

const sf::Event EventQueue::getEvent(int index)
{
    assert(index >= 0 && index < events.size() && "event index must be in range");

    return events[index];
}

std::vector<sf::Event>::const_iterator EventQueue::begin() {return events.begin();}
std::vector<sf::Event>::const_iterator EventQueue::end() {return events.end();}