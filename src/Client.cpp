#include "Client.h"
#include <SFML/Network.hpp>
#include <iostream>


Client::Client()
{
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("localhost", 53000);
    if (status != sf::Socket::Done)
    {
        std::cout << "connected to server: "<< status << '\n';
//        Thread *t = new Thread(deliver);
//        t->send(buffer_pointer);
//        t->joinThread();
    }
}

Client::~Client()
{
    //dtor
}
