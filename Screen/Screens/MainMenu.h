#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics/Text.hpp>
#include "../ScreenEngine.h"
#include "../../Input/Button.h"

namespace pong { namespace screen { 

class MainMenu : public Screen
{
    sf::Text text;

    input::Button playButton;
    input::Button quitButton;

public:
    MainMenu(ScreenConstructionParameters parameters);

    void update(ScreenUpdateParameters)  override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition) override;

    double getTransitionInTime() override;
    double getTransitionOutTime() override;
};

}}

#endif