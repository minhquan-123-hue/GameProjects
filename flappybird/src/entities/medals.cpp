#include <entities/medals.h>
#include <iostream>


Medals::Medals(){}

void Medals::init()
{

    copper_rect.x = 460;
    copper_rect.y = 460;
    copper_rect.w = 150;
    copper_rect.h = 150;

    silver_rect.x = 460;
    silver_rect.y = 460;
    silver_rect.w = 150;
    silver_rect.h = 150;

    gold_rect.x = 460;
    gold_rect.y = 460;
    gold_rect.w = 150;
    gold_rect.h = 150;

}
void Medals::render(SDL_Renderer *renderer , IMGManager &img_manager, int &score)
{
    if (score < 3)
    {
        SDL_RenderCopy(renderer , img_manager.copper , nullptr, &copper_rect);
    }

    if (3 <= score && score < 5)
    {
        SDL_RenderCopy(renderer , img_manager.silver , nullptr, &silver_rect);
    }

    if (score >= 7)
    {
        SDL_RenderCopy(renderer , img_manager.gold, nullptr, &gold_rect);
    }
}