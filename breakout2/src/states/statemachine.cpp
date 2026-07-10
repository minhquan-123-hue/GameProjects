#include "../../lib/states/statemachine.h"

StateMachine::StateMachine()
    : current(nullptr)
{
}

StateMachine::~StateMachine()
{
    if (current)
    {
        current->onExit();
        delete current;
        current = nullptr;
    }
}

void StateMachine::changeState(State *newState)
{
    if (current)
    {
        current->onExit();
        delete current;
        current = nullptr;
    }

    current = newState;
    if (current)
        current->onEnter();
}

State *StateMachine::getCurrent() const
{
    return current;
}
