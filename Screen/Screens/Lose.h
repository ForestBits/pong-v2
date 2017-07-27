//when you lose a game

#ifndef LOSE_H
#define LOSE_H

#include <SFML/Graphics/Text.hpp>
#include "../ScreenEngine.h"
#include "../../Input/Button.h"

namespace pong { namespace screen {

class Lose : public Screen
{
    sf::Text text;

    input::Button playButton;
    input::Button backButton;

public:
    Lose(ScreenConstructionParameters parameters);

    void update(ScreenUpdateParameters parameters) override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition) override;
};

}}

#endif