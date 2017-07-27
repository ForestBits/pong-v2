//choose to be server or client

#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include "../ScreenEngine.h"
#include "../../Input/Button.h"

namespace pong { namespace screen {

class Multiplayer : public Screen
{
    input::Button clientButton;
    input::Button serverButton;
    input::Button backButton;

public:
    Multiplayer(ScreenConstructionParameters parameters);

    void update(ScreenUpdateParameters parameters) override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition) override;
};

}}


#endif