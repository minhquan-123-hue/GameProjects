#include <states/LoseState.h>

LoseState::LoseState():
lose_text("you have ")
{}

void LoseState::init(int &score, SDL_Renderer *renderer , FontManager &font_manager)
{
    font_manager.create_lose(renderer , lose_text, score);
}

bool LoseState::input(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
        {
            return true;
        }
    }

    return false;
}

void LoseState::render(SDL_Renderer *renderer , FontManager &font_manager)
{
    SDL_RenderCopy(renderer , font_manager.lose_texture, nullptr, &font_manager.lose_rect);

}