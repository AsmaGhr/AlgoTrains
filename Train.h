#ifndef TRAIN_H
#define TRAIN_H

#include <Message.h>

using namespace std;

class Train : public Message
{
    public:
        Train();
        virtual ~Train();

    protected:

    private:
        int lc = 0;
        vector<string> circuit = {};
        vector<Wagons> wagons = {};
};

#endif // TRAIN_H
