#pragma once

#include <SDL2/SDL.h>

// Simple State interface. Concrete states derive from this.
class State
{
public:
    // call son destructor
    virtual ~State() {}
    // setup + clean 
    virtual void onEnter() {}
    virtual void onExit() {}
    // each inherit class have to implement this 3 functions 
    virtual void handleInput(const SDL_Event &ev) = 0;
    virtual void update(float dt) = 0;
    virtual void render(SDL_Renderer *renderer) = 0;
};

// Minimal state machine that holds one active state.
class StateMachine
{
public:
    StateMachine();
    ~StateMachine();

    // State and inherit son can write same type 
    void changeState(State *newState);

    // return current type but only read can't change
    State *getCurrent() const;

private:
    State *current;
};