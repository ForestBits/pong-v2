#include "MainMenu.h"
#include "Play.h"
#include "../../Utility/EventQueue.h"

using namespace pong;
using namespace pong::screen;

MainMenu::MainMenu(ScreenConstructionParameters parameters) : playButton(parameters.font, parameters.clickSound), quitButton(parameters.font, parameters.clickSound)
{
    text.setFont(parameters.font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setString("Pong");
    text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
    text.setPosition(320, 50);

    playButton.setPosition({320, 100});
    playButton.setText("Play");
    playButton.setOnClick([parameters] {parameters.control.setScreen<Play>(parameters);});

    quitButton.setPosition({320, 200});
    quitButton.setText("Quit");
    quitButton.setOnClick([] {throw QuitException();});
}

void MainMenu::update(ScreenUpdateParameters parameters)
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
    quitButton.update(events, mousePosition);
}

void MainMenu::draw(sf::RenderTarget & target, const TransitionInfo & transition)
{
    target.clear(sf::Color::Black);

    target.draw(playButton);
    target.draw(quitButton);

    //target.draw(text);
}

double MainMenu::getTransitionInTime() {return 0;}
double MainMenu::getTransitionOutTime() {return 0;}
