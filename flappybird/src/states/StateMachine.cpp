#include <states/StateMachine.h>
#include <iostream>

StateMachine::StateMachine():
currentState(State::MENU),
temp_score(0)
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
        // reset and initialize play state for a fresh match
        play_state.reset();
        play_state.init();
        temp_score = 0;
    }
    else if (state == 'w')
    {
        currentState = State::WAIT;
        // reset wait state so countdown starts fresh
        wait_state.reset();
    }
    else if (state == 'l')
    {
        currentState = State::LOSE;
    }
}

void StateMachine::input(SDL_Event &event, AudioManager &audio_manager)
{

    // menustate take input 
    if (currentState == State::MENU)
    {
        bool return_pressed = menu_state.input(event);
        if (return_pressed)
        {
            change('w');
        }
    }

    // playstate take input 
    if (currentState == State::PLAY)
    {
        play_state.input(event, audio_manager);
    }

    // losestate take input 
    if (currentState == State::LOSE)
    {
        bool is_return = lose_state.input(event);

        if (is_return)
        {
            audio_manager.play_background_music();
            change('w');
        }
    }

}

void StateMachine::process_logic(float dt, SDL_Renderer *renderer, FontManager &font_manager, AudioManager &audio_manager)
{

    if (currentState == State::WAIT)
    {
        bool is_end = wait_state.process_logic(dt,renderer,font_manager);
        if (is_end)
        {
            change('p');
        }
    }

    if (currentState == State::PLAY)
    {
        play_state.process_logic(dt, audio_manager);

        bool is_collided = play_state.collide(audio_manager);

        if (is_collided)
        {
            change('l');

            audio_manager.stop_background_music();   
        }

        temp_score = play_state.score(renderer, font_manager, audio_manager);

        // initialize object lose_state
        lose_state.init(temp_score, renderer, font_manager);
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

    if (currentState == State::LOSE)
    {
        lose_state.render(renderer,f_manager);
    }
}