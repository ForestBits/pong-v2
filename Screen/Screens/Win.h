//when you lose a game

#ifndef WIN_H
#define WIN_H

#include <SFML/Graphics/Text.hpp>
#include "../ScreenEngine.h"
#include "../../Input/Button.h"

namespace pong { namespace screen {

class Win : public Screen
{
    sf::Text text;

    input::Button playButton;
    input::Button backButton;

public:
    Win(ScreenConstructionParameters parameters);

    void update(ScreenUpdateParameters parameters);

    void draw(sf::RenderTarget & target, const TransitionInfo & transition);
};

}}

#endif