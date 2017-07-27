//client, chooses to connect somewhere...

#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include "../ScreenEngine.h"

namespace pong { namespace screen {

class Client : public Screen
{
   sf::TcpSocket socket;

   sf::UdpSocket broadcast;

public:
    Client(ScreenConstructionParameters parameters);

    void update(ScreenUpdateParameters parameters) override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition) override;

};

}}

#endif