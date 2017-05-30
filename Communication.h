#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <iostream>
#include <queue>
#include <thread>
#include <cstdlib>
#include "threadsafe_queue.h"
#include "pugixml.hpp"
#include "AllParticipants.h"
#include "Automate.h"
#include "Participant.h"
#include <SFML/Network.hpp>
#include <vector>



using namespace std;

class Communication
{
    public:
        Communication(void(*fctPtr)(const uint8_t*), void(*viewChange)(bool, Participant&, vector<Participant>&));
        ~Communication();
        void send(const uint8_t* , uint32_t);
        void joinThread();

    private:
        static void deliveryMoinsGourmand(void(*fctPtr)(const uint8_t*));
        static void accept();
        static Automate::states connect();
        static void receive();
        int sendSize(uint32_t);
//        threadsafe_queue<const uint8_t*> tsq;
//        sf::TcpListener listener;
//        sf::TcpSocket client;
//        sf::TcpSocket socket;
//        int connect_me_other = 0;
        std::thread deliveryThread;
        std::thread acceptThread;
        std::thread connectThread;
};

#endif // COMMUNICATION_H
