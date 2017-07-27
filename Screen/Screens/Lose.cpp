#include "MainMenu.h"
#include "Singleplayer.h"
#include "Lose.h"

using namespace pong;
using namespace pong::screen;

Lose::Lose(ScreenConstructionParameters parameters) : backButton(parameters.font, parameters.clickSound), playButton(parameters.font, parameters.clickSound)
{
    text.setFont(parameters.font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setString("You lost!");
    text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
    text.setPosition(320, 150);

    playButton.setText("Play Again");
    playButton.setPosition({320, 300});
    playButton.setOnClick([parameters] {parameters.control.setScreen<Singleplayer>(parameters);});

    backButton.setPosition({320, 400});
    backButton.setText("Menu");
    backButton.setOnClick([parameters] {parameters.control.setScreen<MainMenu>(parameters);});
}

void Lose::update(ScreenUpdateParameters parameters)
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

    playButton.update(events, mousePosition);
    backButton.update(events, mousePosition);
}

void Lose::draw(sf::RenderTarget & target, const TransitionInfo & transition)
{
    target.clear(sf::Color::Black);

    target.draw(text);

    target.draw(playButton);
    target.draw(backButton);
}