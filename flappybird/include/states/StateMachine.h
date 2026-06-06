#pragma once
#include <systems/imagemanager.h>
#include <SDL2/SDL.h>

// state objects
#include <states/MenuState.h>
#include <states/WaitState.h>
#include <states/PlayState.h>
#include <states/LoseState.h>

// systems
#include <systems/FontManager.h>

class StateMachine
{
    public:

    StateMachine();

    void init(SDL_Renderer *renderer, FontManager &font_manager);
    void input(SDL_Event &event);

    void change(char state);
    void process_logic(float dt, SDL_Renderer *renderer, FontManager &font_manager);
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
    WaitState wait_state;
    PlayState play_state;
    LoseState lose_state;

    int temp_score;
};