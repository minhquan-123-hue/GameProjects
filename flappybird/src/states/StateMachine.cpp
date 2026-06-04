#include <states/StateMachine.h>
#include <iostream>

StateMachine::StateMachine():
currentState(State::MENU),
is_collided(false)
{}

void StateMachine::init(SDL_Renderer *renderer, FontManager &font_manager)
{   
    menu_state.init(renderer, font_manager);
    play_state.init();
}

void StateMachine::change(char state)
{
    if (state == 'm')
    {
        currentState = State::MENU;
    }
    else if (state == 'p')
    {
        currentState = State::PLAY;
    }
    else if (state == 'w')
    {
        currentState = State::WAIT;
    }
    else if (state == 'l')
    {
        currentState = State::LOSE;
    }
}

void StateMachine::input(SDL_Event &event)
{

    if (currentState == State::MENU)
    {
        bool return_pressed = menu_state.input(event);
        if (return_pressed)
        {
            change('w');
        }
    }

    if (currentState == State::PLAY)
    {
        play_state.input(event);
    }


}

void StateMachine::process_logic(float dt, SDL_Renderer *renderer, FontManager &font_manager)
{

    if (currentState == State::WAIT)
    {
        bool is_endwait = wait_state.process_logic(dt,renderer,font_manager);
        if (is_endwait)
        {
            change('p');
        }
    }

    if (currentState == State::PLAY)
    {
        play_state.process_logic(dt);

        is_collided = play_state.collide();

        if (is_collided)
        {
            change('l');   
        }

        int point = play_state.score(renderer, font_manager);
        std::cout << point << std::endl;
    }
}

void StateMachine::render(SDL_Renderer *renderer, IMGManager &img_manager, FontManager &f_manager)
{
    if (currentState == State::MENU)
    {
        menu_state.render(renderer, f_manager);
    }

    if (currentState == State::WAIT)
    {
        wait_state.render(renderer,f_manager);
    }

    if (currentState == State::PLAY)
    {
        play_state.render(renderer,img_manager,f_manager);
    }   
}