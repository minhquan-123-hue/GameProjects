#pragma once
#include <systems/imagemanager.h>
#include <SDL2/SDL.h>

// state objects
#include <states/MenuState.h>

// systems
#include <systems/FontManager.h>

class StateMachine
{
    public:

    StateMachine();

    void init(SDL_Renderer *renderer, FontManager &font_manager);
    void input(SDL_Event &event);

    void change(char state);
    void process_logic(float dt);
    void render(SDL_Renderer *renderer, IMGManager &img_manager, FontManager &f_manager);

    enum class State
    {
        MENU,
        WAIT,
        PLAY,
        LOSE
    };

    State currentState;

    MenuState menu_state;

};