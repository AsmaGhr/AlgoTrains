#include "Participant.h"

Participant::Participant()
{

}

Participant::Participant(std::string h,int p)
{
    host=h;
    port=p;
}

Participant::~Participant()
{
    //dtor
}

std::string Participant::getHost()
{
    return host;
}

int Participant::getPort()
{
    return port;
}

void Participant::setPort(int p)
{
    port=p;
}

//ostream &operator<<(ostream &os, Participant const &)
//{
//    os << host << " : " << port;
//    return os;
//}
