#ifndef MESSAGE_H
#define MESSAGE_H


class Message
{
    public:
        Message();
        virtual ~Message();
        enum type{INSERT, TRAIN, ACK_INSERT,NEW_SUCC, PERTE_CONN};


    protected:

    private:
        type msgType;
        Participant source;
};

#endif // MESSAGE_H
