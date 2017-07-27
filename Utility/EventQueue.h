//way to pass SFML events to multiple things

#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <SFML/Window/Event.hpp>
#include <vector>

namespace pong {

class EventQueue
{
    std::vector<sf::Event> events;

public:
    EventQueue(sf::Window & window);

    int getCount();

    const sf::Event getEvent(int index);

    std::vector<sf::Event>::const_iterator begin();
    std::vector<sf::Event>::const_iterator end();
};

}

#endif