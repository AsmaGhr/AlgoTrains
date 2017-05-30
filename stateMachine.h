#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

enum class Triggers { LostConnection, NewConnection, ReceivedMsg, SendMsg, Start2Alone };

void initStatemachine();
void executeTransition(Triggers const,char const * const);

#endif // STATE_MACHINE_H
