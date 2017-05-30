#include "Wagon.h"

Wagon::Wagon()
{
    //ctor
}

Wagon::~Wagon()
{
    //dtor
}

Wagon::ajouterMsg(string msg)
{
    message.push(msg);
}

Wagon::deliverMsg(queue<string> deliverQueue)
{
    while(message.size()>0)
    {
        deliverQueue.push(message.front());
        message.pop();
    }
}
