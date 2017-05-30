#include "Automate.h"
#include "Participant.h"

#include<vector>
#include <iostream>

Automate::Automate()
{
    this->currentState = start;
}

Automate::~Automate()
{
    //dtor
}
 void Automate::addProcess(Participant p){
    process.push_back(p);
    if(process.size() == 1)
    {
        setState(alone);
    }
    else
    {
        setState(multiple);
    }
 }

void Automate::dropProceess(Participant p){
    int i = 0;
    while( i < process.size() && (process[i].getHost()!=p.getHost() || process[i].getPort()!=p.getPort()))
    {
        i++;
    };
    process.erase(process.begin()+i);
    if(i==process.size()){
       std::cout << "sorry , this process dosen't exist";
    }
    if(process.size() == 1)
    {
        setState(alone);
    }
    else
    {
        setState(multiple);
    }
}

Automate::states Automate::getState(){
    return this->currentState;
}

void Automate::setState(states state){
    this->currentState = state ;

}
