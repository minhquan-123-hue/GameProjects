#include "../../lib/states/statemachine.h"

StateMachine::StateMachine()
    : current(nullptr)
{
}

StateMachine::~StateMachine()
{
    // this is for the last state , when you quit the game
    if (current)
    {
        // use the fucntion onExit of the son == clean() 
        // free value after jump to other state
        current->onExit();
        // also delete the pointer on the heap store old state
        delete current;
        // assign "nothing" to that pointerpointer
        current = nullptr;
    }
}

void StateMachine::changeState(State *newState)
{
    // this is "clean" during the game running
    // between jump to other state
    if (current)
    {
        current->onExit();
        delete current;
        current = nullptr;
    }

    // assgin the newstate to variable 
    // like i said , other son class == same blood
    // so i can have State type stand before
    current = newState;
    if (current)
        // setup if need
        current->onEnter();
}

// return current type but only can't modify
State *StateMachine::getCurrent() const
{
    return current;
}
