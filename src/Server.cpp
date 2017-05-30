#include "Server.h"
#include <iostream>

#include <SFML/Network.hpp>

Server::Server()
{
   sf::TcpListener listener;

    // lie l'écouteur à un port
    if (listener.listen(53000) == sf::Socket::Done)
    {
        std::cout << "Listening: " << '\n';
    }

    // accepte une nouvelle connexion
    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done)
    {
        // erreur...
    }

}

Server::~Server()
{
    //dtor
}
