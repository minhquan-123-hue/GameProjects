#include <states/StateMachine.h>

StateMachine::StateMachine():
currentState(State::MENU)
{}

void StateMachine::init(SDL_Renderer *renderer, FontManager &font_manager)
{   
    menu_state.init(renderer, font_manager);
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
            change('p');
        }
    }

}

void StateMachine::process_logic(float dt)
{

}

void StateMachine::render(SDL_Renderer *renderer, IMGManager &img_manager, FontManager &f_manager)
{
    if (currentState == State::MENU)
    {
        menu_state.render(renderer, f_manager);
    }
}