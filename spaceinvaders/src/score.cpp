#include <score.h>

ScoreUI::ScoreUI() : font(nullptr) {}
ScoreUI::~ScoreUI()
{
    clean();
}

void ScoreUI::createFrame()
{

    horRect.x = 0;
    horRect.y = 100;
    horRect.w = 1000;
    horRect.h = 10;

    verRect.x = 498;
    verRect.y = 0;
    verRect.w = 4;
    verRect.h = 100;
}

void ScoreUI::renderFrame(SDL_Renderer *renderer, SDL_Rect &horRect, SDL_Rect &verRect)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // tô màu
    SDL_RenderFillRect(renderer, &horRect);
    SDL_RenderFillRect(renderer, &verRect);
}

void ScoreUI::clean()
{
}
