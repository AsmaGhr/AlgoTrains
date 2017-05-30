#ifndef NEWSUCC_H
#define NEWSUCC_H

#include <Message.h>


class NEWSUCC : public Message
{
    public:
        NEWSUCC();
        virtual ~NEWSUCC();

    protected:

    private:
        Participant newSucc;
};

#endif // NEWSUCC_H
