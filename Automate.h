#ifndef AUTOMATE_H
#define AUTOMATE_H
#include <vector>
#include <iostream>
#include "Participant.h"
class Automate
{
    public:
        Automate();
        virtual ~Automate();
        enum states {start , alone , multiple };
        void addProcess(Participant);
        void dropProceess(Participant);
        states getState();
        void setState(states);
    protected:
    private:
        states currentState ;
        std::vector<Participant> process ;
};

#endif // AUTOMATE_H
