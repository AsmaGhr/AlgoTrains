#ifndef PARTICIPANT_H
#define PARTICIPANT_H
#include <string>
#include <iostream>



class Participant
{
    public:
        Participant();
        Participant(std::string h,int p);
        ~Participant();
        std::string getHost();
        int getPort();
        void setHost(std::string);
        void setPort(int );
        bool operator==(Participant&);
        friend std::ostream &operator<<(std::ostream&, Participant const&);
    protected:
    private:
        std::string host;
        int port;
};

#endif // PARTICIPANT_H
