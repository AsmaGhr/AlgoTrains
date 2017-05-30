#ifndef INSERT_H
#define INSERT_H

#include <Message.h>


class INSERT : public Message
{
    public:
        INSERT();
        virtual ~INSERT();

    protected:

    private:
        Participant pred;
};

#endif // INSERT_H
