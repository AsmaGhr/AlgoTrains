#include "Train.h"

Train::Train(vector<string> circuitArg, vector<Wagon> wagonsArg )
{
    this.circuit = circuitArg;
    this.wagons = wagonsArg;
}

Train::~Train()
{
    //dtor
}
