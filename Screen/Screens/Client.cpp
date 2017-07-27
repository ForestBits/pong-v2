#include <iostream>
#include "Client.h"

using namespace pong;
using namespace pong::screen;

Client::Client(ScreenConstructionParameters parameters)
{
    socket.setBlocking(false);
}

void Client::update(ScreenUpdateParameters parameters)
{
    sf::Packet packet;

    broadcast.send(packet, sf::IpAddress::Broadcast, 11111);
}

void Client::draw(sf::RenderTarget & target, const TransitionInfo & transition)
{
    target.clear(sf::Color::Red);
}