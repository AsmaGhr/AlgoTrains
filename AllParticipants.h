#ifndef ALLPARTICIPANTS_H
#define ALLPARTICIPANTS_H
#include "Participant.h"
#include<vector>


class AllParticipants
{
    public:
        AllParticipants();
        ~AllParticipants();
        Participant me();
        Participant other(int);
        void displayParticipants();
        std::string getHostName();
        int occurrenceHost(std::string);
        Participant getPartByHost(std::string  );
        void createDisplayOthers();
        bool correspHostPort(std::string ,int );
        bool isParticipantUsed(Participant);




    protected:
    private:
        std::vector<Participant> vectParticipants;
        Participant *p_me;
        Participant *p_other;
        std::vector<Participant> vectOthers;
        std::string trainsPort;
        std::vector<Participant> usedParticipants;

};

#endif // ALLPARTICIPANTS_H
