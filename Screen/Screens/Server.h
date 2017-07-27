//server, waits for connections

#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include "../ScreenEngine.h"

namespace pong { namespace screen {

class Server : public Screen
{
   sf::TcpSocket socket;

   sf::UdpSocket broadcastDetector;

public:
    Server(ScreenConstructionParameters parameters);

    void update(ScreenUpdateParameters parameters) override;

    void draw(sf::RenderTarget & target, const TransitionInfo & transition) override;
};

}}

#endif