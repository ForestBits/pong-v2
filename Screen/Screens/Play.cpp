#include "Play.h"
#include "MainMenu.h"
#include "Singleplayer.h"
#include "Multiplayer.h"

using namespace pong;
using namespace pong::screen;

Play::Play(ScreenConstructionParameters parameters) : singleplayerButton(parameters.font, parameters.clickSound),
                                                                                 multiplayerButton(parameters.font, parameters.clickSound),
                                                                                 backButton(parameters.font, parameters.clickSound)
{
    singleplayerButton.setPosition({320, 50});
    singleplayerButton.setText("Single Player");
    singleplayerButton.setOnClick([parameters] {parameters.control.setScreen<Singleplayer>(parameters);});

    multiplayerButton.setPosition({320, 100});
    multiplayerButton.setText("Multi Player");
    multiplayerButton.setOnClick([parameters] {parameters.control.setScreen<Multiplayer>(parameters);});

    backButton.setPosition({320, 400});
    backButton.setText("Menu");
    backButton.setOnClick([parameters] {parameters.control.setScreen<MainMenu>(parameters);});
}

void Play::update(ScreenUpdateParameters parameters)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        throw QuitException();

    EventQueue events(parameters.window);

    for (sf::Event event : events)
    {
        if (event.type == sf::Event::Closed)
            throw QuitException();
    }

    sf::Vector2i mousePosition = getMousePosition(parameters.window);

    singleplayerButton.update(events, mousePosition);
    multiplayerButton.update(events, mousePosition);
    backButton.update(events, mousePosition);
}

void Play::draw(sf::RenderTarget & target, const TransitionInfo & transition)
{
    target.clear(sf::Color::Black);

    target.draw(singleplayerButton);
    target.draw(multiplayerButton);
    target.draw(backButton);
}