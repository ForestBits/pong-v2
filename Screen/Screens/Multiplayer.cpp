#include "Multiplayer.h"
#include "MainMenu.h"
#include "Client.h"
#include "Server.h"
#include "Play.h"

using namespace pong;
using namespace pong::screen;

Multiplayer::Multiplayer(ScreenConstructionParameters parameters) : clientButton(parameters.font, parameters.clickSound),
                                                                                                        serverButton(parameters.font, parameters.clickSound),
                                                                                                        backButton(parameters.font, parameters.clickSound)
{
    clientButton.setText("Client");
    clientButton.setPosition({320, 100});
    clientButton.setOnClick([parameters] {parameters.control.setScreen<Client>(parameters);});

    serverButton.setText("Server");
    serverButton.setPosition({320, 200});
    serverButton.setOnClick([parameters] {parameters.control.setScreen<Server>(parameters);});

    backButton.setPosition({320, 400});
    backButton.setText("Back");
    backButton.setOnClick([parameters] {parameters.control.setScreen<Play>(parameters);});
}

void Multiplayer::update(ScreenUpdateParameters parameters)
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

    clientButton.update(events, mousePosition);
    serverButton.update(events, mousePosition);
    backButton.update(events, mousePosition);
}

void Multiplayer::draw(sf::RenderTarget & target, const TransitionInfo & transition)
{
    target.clear(sf::Color::Black);

    target.draw(clientButton);
    target.draw(serverButton);
    target.draw(backButton);
}