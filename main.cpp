#include <iostream>
#include <queue>
#include "Communication.h"
#include "include/Server.h"
#include "flatbuffers.h"
#include "Message_generated.h"
#include "Participant.h"

using namespace Message;
using namespace std;


void deliver(const uint8_t* buff)
{
    auto recu = GetMsg(buff);
    float xR = recu->x();
    std::cout << "message n° delivered : "<< xR << '\n';
    string msgR = recu->message()->c_str();
    string msgO = recu->objet()->c_str();
    cout << msgO << '\n';
    cout << msgR << '\n';
}

void view_change(bool goneProcess, Participant& concernedProcess, vector<Participant>& participants)
{
    if (goneProcess)
    {
        cout<< "gone";
    } else {
        cout<< "arrived";
    }
    cout << " process " ;
    cout << concernedProcess.getHost() << " : " << concernedProcess.getPort()<< endl;
    cout << endl ;
    for (uint32_t i=0; i<participants.size(); i++)
    {
        cout << participants[i].getHost() << "\n";
    }
}

int main()
{
    flatbuffers::FlatBufferBuilder builder;
    uint32_t size = builder.GetSize();
    float x = 1;
    auto msg = builder.CreateString("Ceci est un message de test 1");
    auto obj = builder.CreateString("Test objet 1");
    auto message = CreateMsg(builder, obj, msg, x);
    builder.Finish(message);
    uint8_t *buf = builder.GetBufferPointer();
    size = builder.GetSize();
    Communication *com = new Communication(deliver, view_change);
    try
    {
        com->send(buf, size);
        com->send(buf, size);
    }
    catch(std::string error)
    {
        cerr << error << endl;
    }
    com->joinThread();
    return 0;
}
