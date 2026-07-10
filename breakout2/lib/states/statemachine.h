#pragma once

#include <SDL2/SDL.h>

// Simple State interface. Concrete states derive from this.
class State
{
public:
    virtual ~State() {}
    virtual void onEnter() {}
    virtual void onExit() {}
    virtual void handleInput(const SDL_Event &ev) = 0;
    virtual void update() = 0;
    virtual void render(SDL_Renderer *renderer) = 0;
};

// Minimal state machine that holds one active state.
class StateMachine
{
public:
    StateMachine();
    ~StateMachine();

    void changeState(State *newState);

    State *getCurrent() const;

private:
    State *current;
};