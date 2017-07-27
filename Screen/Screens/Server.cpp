#include <iostream>
#include "Server.h"

using namespace pong;
using namespace pong::screen;

Server::Server(ScreenConstructionParameters parameters)
{


    socket.setBlocking(false);

    broadcastDetector.bind(11111);
}

void Server::update(ScreenUpdateParameters parameters)
{
    sf::Packet packet;

    sf::IpAddress remote;

    unsigned short port;

    if (broadcastDetector.receive(packet, remote, port) == sf::Socket::Done)
    {
        sf::Int8 number;

        packet >> number;

        //magic number? Oh yes
        if (number == 56)
        {
            //if (socket.connect())
        }
    }
}

void Server::draw(sf::RenderTarget & target, const TransitionInfo & transition)
{
    target.clear(sf::Color::Blue);
}