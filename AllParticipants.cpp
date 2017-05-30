#include "AllParticipants.h"
#include "pugixml.hpp"
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <limits.h>

AllParticipants::AllParticipants()
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("tree.xml");
    std::cout << "Load result: " << result.description() << std::endl;
    pugi::xml_node participants = doc.child("participants");
    std::cout <<participants.name() << std::endl;
    //automatic access to xml file and fill vectParticipants
    for (pugi::xml_node participant = participants.first_child(); participant; participant = participant.next_sibling())
    {
        std::string h=participant.attribute("host").as_string();
        int p=participant.attribute("port").as_int();
        Participant newParticipant=Participant(h,p);
        vectParticipants.push_back(newParticipant);
    }
    //test selon occHost
    std::string s=getHostName();
    int occHost=occurrenceHost(s);
    if(occHost==0)
    {
        std::cout<<"your hostname doesn't exist in the xml file"<<std::endl;
    }
    else if(occHost==1)
    {
        std::cout<<"your hostname exists in the xml file 1 time"<<std::endl;
        Participant ret = getPartByHost(s);
        p_me=new Participant;
        *p_me=ret;
    }
        //occHost>1
    else
    {
        std::string trainsPort=getenv("TRAINS_PORT");
        int p=atoi(trainsPort.c_str());
        std::cout<<"TRAINS_PORT: "<<p<<std::endl;
        std::cout<<"hostname "<<s<<std::endl;
        if(correspHostPort(s,p))
        {
            std::cout<<"host matchs port "<<std::endl;
            p_me=new Participant(s,p);
            if(isParticipantUsed(*p_me))
            {
                std::cout<<"this port is used, choose another one"<<std::endl;
            }
            else
            {
                usedParticipants.push_back(*p_me);//usedParticipant doit etre partagé entre les differents utilisateurs!!!!!!
                //viewChange
                std::cout<<"this port is not used"<<std::endl;
            }
        }
        else
        {
            std::cout<<"hostname doesn't match port "<<std::endl;
        }
    }
}

AllParticipants::~AllParticipants()
{
   delete p_me;
   delete p_other;
}

Participant AllParticipants::me()
{
    return *p_me;
}

Participant AllParticipants::other(int i)
{
    Participant p=vectOthers[i];
    std::string hs=p.getHost();
    int por=p.getPort();
    p_other=new Participant(hs,por);
    return *p_other;
}

void AllParticipants::createDisplayOthers()
{
    for(int i=0;i<(int)vectParticipants.size();i++)
    {
        Participant p=vectParticipants[i];
        if(p.getHost()!=p_me->getHost() || p.getPort()!=p_me->getPort() )
        {
            vectOthers.push_back(p);
        }
    }
    std::cout<<std::endl;
    std::cout<<"Information about other participants: "<<std::endl;
    //std::cout<<"size of vectOthers= "<<vectOthers.size()<<std::endl;
    for(int i=0;i<(int)vectOthers.size();i++)
    {
        Participant p=vectOthers[i];
        std::cout<<"hostname: "<<p.getHost()<<", port: "<<p.getPort()<<std::endl;
    }


     //p_me=new Participant(s,p);
}


void AllParticipants::displayParticipants()
{
    std::cout<<std::endl;
    std::cout<<"vectParticipants content :"<<std::endl;
    for(int i=0;i<(int)vectParticipants.size();i++)
    {
        Participant p=vectParticipants[i];
        std::cout<<p.getHost()<<"**"<<p.getPort()<<std::endl;
    }
}

std::string AllParticipants::getHostName()
{
    char hostname[250];
    gethostname(hostname, 250);
    std::string ret(hostname);
    return ret;
}

int AllParticipants::occurrenceHost(std::string s )
{

    int occ=0;
    for(int i=0;i<(int)vectParticipants.size();i++)
    {
        if(vectParticipants[i].getHost() == s)
        {
            occ++;
        }
    }
    return occ;
}

Participant AllParticipants::getPartByHost(std::string hst )
{
    Participant res;
    int i=0;
    bool findIt=false;
    while((findIt==false)&& (i<(int)vectParticipants.size()))
    {
        Participant p=vectParticipants[i];
        if(p.getHost()==hst)
        {
            res=p;
            findIt=true;
        }
        else
        {
            i++;
        }

    }
    return res;
}

bool AllParticipants::correspHostPort(std::string h, int p)
{
    for(int i=0;i<(int)vectParticipants.size();i++)
    {
        Participant pa=vectParticipants[i];
        if((pa.getHost()==h)&&(pa.getPort()==p))
        {
            return true;
        }
    }
    return false;
}

bool AllParticipants::isParticipantUsed(Participant p)
{
    for(int i=0;i<(int)usedParticipants.size();i++)
    {

        Participant pa=usedParticipants[i];
        if((pa.getHost()==p.getHost())&&((pa.getPort()==p.getPort())))
        {
            return true;
        }
    }
    return false;
}
