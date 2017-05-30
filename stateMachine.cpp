#include <iostream>
#include <memory>
#include "fsm.h"
#include "stateMachine.h"

using namespace std;

enum class States { Start, Alone, Multi };

static string States2str[] = { "Start", "Alone", "Multi" };
static string Triggers2str[] = { "LostConnection", "NewConnection", "ReceivedMsg", "SendMsg", "Start2Alone" };

static FSM::Fsm<States, States::Start, Triggers> fsm;

struct PushMe { char const *data; };
using PushMe_t = std::shared_ptr<PushMe>;
PushMe_t push_me = std::make_shared<PushMe>();

void manageLostConnection(PushMe_t p)
{
    string s{p->data};
    cout << "manageLostConnection() is called with data '" << s << "'" << endl;
}

void manageNewConnectionWhenAlone(PushMe_t p)
{
    string s{p->data};
    cout << "manageNewConnectionWhenAlone() is called with data '" << s << "'" << endl;
}

void manageNewConnectionWhenStart(PushMe_t p)
{
    string s{p->data};
    cout << "manageNewConnectionWhenStart() is called with data '" << s << "'" << endl;
}

void sendMsgWhenAlone(PushMe_t p)
{
    string s{p->data};
    cout << "sendMsgWhenAlone() is called with data '" << s << "'" << endl;
}

void sendMsgWhenMulti(PushMe_t p)
{
    string s{p->data};
    cout << "sendMsgWhenMulti() is called with data '" << s << "'" << endl;
}

void start2Alone(PushMe_t p)
{
    string s{p->data};
    cout << "start2Alone() is called with data '" << s << "'" << endl;
}

void initStatemachine()
{
	fsm.add_transitions({
		//  from state ,to state  ,triggers        ,guard                    ,action
		{ States::Start  ,States::Alone ,Triggers::Start2Alone  , nullptr  , bind(start2Alone, push_me) },
		{ States::Start  ,States::Multi ,Triggers::NewConnection  , nullptr  , bind(manageNewConnectionWhenStart, push_me) },

		{ States::Alone  ,States::Alone ,Triggers::SendMsg  , nullptr  , bind(sendMsgWhenAlone, push_me) },
		{ States::Alone  ,States::Multi ,Triggers::NewConnection  , nullptr  , bind(manageNewConnectionWhenAlone, push_me) },

		{ States::Multi  ,States::Multi ,Triggers::SendMsg  , nullptr  , bind(sendMsgWhenMulti, push_me) },
		{ States::Multi  ,States::Alone ,Triggers::LostConnection  , nullptr  , bind(manageLostConnection, push_me) },

	});
}

void executeTransition(Triggers const trigger, char const * const data)
{
    push_me->data = data;
    if (fsm.execute(trigger) != FSM::Fsm_Success) {
        cout << "WARNING : In state " << States2str[static_cast<int>(fsm.state())] << ", received trigger " << Triggers2str[static_cast<int>(trigger)];
        cout << " (and there is no corresponding transition)" << endl;
    }
}

