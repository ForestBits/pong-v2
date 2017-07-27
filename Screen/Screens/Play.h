//singleplayer or multiplayer

#ifndef PLAY_H
#define PLAY_H

#include "../ScreenEngine.h"
#include "../../Input/Button.h"

namespace pong { namespace screen {

class Play : public Screen
{
    input::Button singleplayerButton;
    input::Button multiplayerButton;
    input::Button backButton;

public:
    Play(ScreenConstructionParameters parameters);

    void update(ScreenUpdateParameters parameters) override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition) override;
};



}}

#endif