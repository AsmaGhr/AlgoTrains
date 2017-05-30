#ifndef ACK_INSERT_H
#define ACK_INSERT_H

#include <Message.h>


class ACK_INSERT : public Message
{
    public:
        ACK_INSERT();
        virtual ~ACK_INSERT();

    protected:

    private:
        Participant newPred;
};

#endif // ACK_INSERT_H
