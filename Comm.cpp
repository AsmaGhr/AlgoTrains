#include "Comm.h"
#include "threadsafe_queue.h"
#include "pugixml.hpp"
#include "AllParticipants.h"
#include "Participant.h"
#include "flatbuffers.h"
#include "Automate.h"
#include "stateMachine.h"
#include "Message_generated.h"
#include <thread>
#include <SFML/Network.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace Message;
using namespace std;
vector<Participant> view;
Participant me;
Participant other;
threadsafe_queue<const uint8_t*> tsq;
sf::TcpListener listener;
sf::TcpSocket client;
sf::TcpSocket socket;
int connect_me_other = 0;
void (*viewChange)(bool, Participant&, vector<Participant>&);
Automate automate;
//recopier et mettre extern

Comm::Comm(void(*fctPtr)(const uint8_t*), void(*viewChangeArg)(bool, Participant&, vector<Participant>&))
{
    //Myfunc myFunc(viewChange, receive);
    //CommunicationContext * pctxt = new...
    viewChange = viewChangeArg;
    deliveryThread = std::thread(deliveryMoinsGourmand, fctPtr);
    AllParticipants allParticipants;
    allParticipants.createDisplayOthers();
    me= allParticipants.me();
    other= allParticipants.other(0);
    view.push_back(me);

    initStatemachine();

    automate.addProcess(me);
    cout << automate.getState() << endl;
    if (listener.listen(me.getPort()) != sf::Socket::Done)
    {
        std::cerr << "port already used " << '\n';
        throw ("error listen");
        //exit(EXIT_FAILURE);
    }

    executeTransition(Triggers::Start2Alone, "starting");

    std::cout << "Listening: " << '\n';
    acceptThread = std::thread(accept);
    connect();
}

Comm::~Comm()
{
    std::terminate();
    //delete pctxt
}

//void Communication::deliveryMoinsGourmand(void(*fctPtr)(const uint8_t*), threadsafe_queue<const uint8_t*> *threadSafeQueue)
void Comm::deliveryMoinsGourmand(void(*fctPtr)(const uint8_t*))
{
    while(1)
    {
        const uint8_t *u;
        tsq.wait_and_pop(u);
        fctPtr(u);
    }
}

void Comm::accept()
{
    while (1)
    {
        if (listener.accept(client) == sf::Socket::Done)
        {
            executeTransition(Triggers::NewConnection, "accepted");
            //if (connect_me_other == 0)
            //if (automate.getState()== Automate::alone)
            {
                connect();
            }
            std::cout << "Accept " << '\n';
            std::thread receiveThread = std::thread(receive);
            receiveThread.join();
        }
        else
        {
            std::cout << "Error accept: " << '\n';
            exit(EXIT_FAILURE);
        }
    }
}

Automate::states Communication::connect()
{
    if (automate.getState()==Automate::alone)
    {
        unsigned int port = (unsigned int)other.getPort();
        sf::Socket::Status status = socket.connect(sf::IpAddress(other.getHost()) , port );
        if (status != sf::Socket::Done)
        {
            std::cout << "Error connected to server: "<< status << '\n';
            return(automate.getState());
        }
        automate.addProcess(other);
        executeTransition(Triggers::NewConnection, "connected");
        std::cout << "add: "<< automate.getState() << '\n';
        view.push_back (other);
        viewChange(0, other, view);
        std::cout << "Connected, con_me_other = "<< connect_me_other << " ; status = " << status<< '\n';
        return(automate.getState());
    }
    return(automate.getState());
}

int Communication::sendSize(const uint32_t i)
{
    if (socket.send(&i, sizeof(i)) != sf::Socket::Done)
    {
        std::cout << "Error sending size "<< '\n';
        return 0;
    }
    else
    {
        std::cout << "Size sent " << std::endl;
        return 1;
    }
}

void Communication::send(const uint8_t* i, uint32_t size)
{
    if (automate.getState()== Automate::multiple)
    {
        executeTransition(Triggers::SendMsg, "sending msg");

        if (sendSize(size) == 1)
        {
            if (socket.send((const uint8_t *)i, size) != sf::Socket::Done)
            {
                std::cout << "Error send "<< '\n';
            }
            else
            {
                std::cout << "Sent " << std::endl;
            }
        }
    }
    tsq.push(i);
}

void Communication::receive()
{
    while (1)
    //while(client.getRemoteAddress()!= sf::IpAddress::None && client.getRemotePort()!=0)
    {
        uint32_t len;
        std::size_t received;
        sf::Socket::Status recStatus = client.receive(&len, sizeof(len),received);
        if (recStatus != sf::Socket::Done)
        {
            if (recStatus == sf::Socket::Disconnected || recStatus == sf::Socket::Error)
            {
                automate.setState(Automate::alone);
                executeTransition(Triggers::LostConnection, "connection lost");
                break;
            }
    //         (*viewChange)(1, other, view);
            //throw string("Error received ");
        }
        else
        {
            if (received != sizeof(len))
            {
                std::cout << "Size doesn't match" << received << "!=" << len << std::endl;
                //throw std::string("Size doesn't match");
                continue;
            }
            else
            {
                std::cout << "Received Size " << received << std::endl;
                std::cout << "Received SizeMsg " << len << std::endl;
            }

        }
        uint32_t size = len;
        std::cout << "size is"<< size <<'\n';
        uint8_t* data = new uint8_t[size];
        recStatus = client.receive(data, size, received);
        if (recStatus != sf::Socket::Done)
        {
            if(recStatus == sf::Socket::Disconnected || recStatus == sf::Socket::Error)
            {
                automate.setState(Automate::alone);
                executeTransition(Triggers::LostConnection, "connection lost");
                break;
            }
        }
        else
        {
            std::cout << "Received " << received << " bytes"<< data << std::endl;
            tsq.push(data);
            //Au lieu de ce push : appeler l'automate => message event
        }
    }
}

void Communication::joinThread()
{
   deliveryThread.join();
   acceptThread.join();
}
