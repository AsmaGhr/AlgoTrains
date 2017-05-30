#ifndef WAGON_H
#define WAGON_H


class Wagon
{
    public:
        Wagon();
        virtual ~Wagon();

    protected:

    private:
        queue<string> message;
};

#endif // WAGON_H
