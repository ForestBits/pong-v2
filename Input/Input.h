//all input elements should implement this 

#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
#include "../Utility/EventQueue.h"

namespace pong { namespace input {

class Input : public sf::Drawable
{
public:
    virtual void update(EventQueue events, const sf::Vector2i & mousePosition) = 0;
};

}}

#endif
